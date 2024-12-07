// Fill out your copyright notice in the Description page of Project Settings.


#include "GoBoard.h"
#include "GoGameInfo.h"
#include "Camera/CameraActor.h"
#include "Camera/CameraComponent.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h"
#include "EngineUtils.h"

// Sets default values
AGoBoard::AGoBoard() : x(9), y(9)
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	boxComponent->SetBoxExtent(FVector(600.0f, 600.0f, 600.0f));
	SetRootComponent(boxComponent);

	goBoardMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Old Clock Mesh"));
	goBoardMesh->SetupAttachment(boxComponent);

	audioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Sound Component"));
	audioComponent->SetupAttachment(boxComponent);
}

// Called when the game starts or when spawned
void AGoBoard::BeginPlay()
{
	Super::BeginPlay();

	player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	playerController = GetWorld()->GetFirstPlayerController();

	if (player == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Player does not exist."));
		return;
	}

	if (playerController == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Player controller does not exist."));
		return;
	}

	UInputComponent* playerInputComponent = player->InputComponent;

	if (playerInputComponent == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Player Input Component does not exist."));
		return;
	}

	// arrow에 설정된 블루프린트 클래스가 유효한지 확인
	if (arrow == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("arrow is not set!"));
		return;
	}

	// 스폰 파라미터 설정
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	// 블루프린트 클래스에서 액터 생성
	FVector spawnLocation = FVector(0.0f, 0.0f, 0.0f); // 원하는 스폰 위치
	FRotator spawnRotation = FRotator::ZeroRotator;    // 원하는 회전 값

	spawnedArrow = GetWorld()->SpawnActor<AActor>(arrow, spawnLocation, spawnRotation, SpawnParams);

	// boxComponent에 goBoardMesh를 붙이고 위치 설정
	spawnedArrow->AttachToComponent(boxComponent, FAttachmentTransformRules::KeepRelativeTransform);
	spawnedArrow->SetActorRelativeLocation(FVector(0.0f, 0.0f, CENTER_Y));

	EnableInput(playerController);
	playerInputComponent->BindAction(TEXT("Interaction"), IE_Pressed, this, &AGoBoard::PlayGame);
	playerInputComponent->BindAction(TEXT("Up"), IE_Pressed, this, &AGoBoard::MoveToUp);
	playerInputComponent->BindAction(TEXT("Down"), IE_Pressed, this, &AGoBoard::MoveToDown);
	playerInputComponent->BindAction(TEXT("Left"), IE_Pressed, this, &AGoBoard::MoveToLeft);
	playerInputComponent->BindAction(TEXT("Right"), IE_Pressed, this, &AGoBoard::MoveToRight);
	playerInputComponent->BindAction(TEXT("Place"), IE_Pressed, this, &AGoBoard::PlayerPlace);
	playerInputComponent->BindAction(TEXT("Cancel"), IE_Pressed, this, &AGoBoard::Clear);

	playerMovementComponent = Cast<ACharacter>(player)->GetCharacterMovement();

	if (!IsValid(playerMovementComponent))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Player Movement Component is not set!"));
		return;
	}
}

// Called every frame
void AGoBoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	hasClosePlayer = CheckPlayerIsClose();

	if (isPlay)
		Run();
}

// Called to bind functionality to input
void AGoBoard::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool AGoBoard::CheckPlayerIsClose()
{
	if (player == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Player does not exist."));
		return false;
	}

	// 플레이어와 해당 오브젝트 위치를 구함
	FVector position = GetActorLocation();
	FVector playerPosition = player->GetActorLocation();

	// 플레이어와 해당 오브젝트 거리를 구함
	float distance = FVector::Dist(position, playerPosition);

	return distance <= interactionDistance;
}

void AGoBoard::ChangeToGameCamera()
{
	if (startCamera == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Camera Change Fail!!"));
		return;
	}

	// 플레이어의 뷰 타겟(View Target)을 해당 카메라로 전환
	playerController->SetViewTargetWithBlend(
		startCamera, // 새로운 뷰 타겟
		0.0f,        // 블렌드 시간 (0.0초)
		EViewTargetBlendFunction::VTBlend_Linear, // 블렌드 함수 (선형)
		0.0f,        // 블렌드 지수 (Exponent)
		false        // 기존 뷰 타겟 잠금 여부
	);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Camera Change Succeed!!"));

	AIPlace();
}

void AGoBoard::FindPlayerCamera()
{
	// 플레이어 컨트롤러가 존재하는지 확인
	if (playerController == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("PlayerController not found!"));
		return;
	}

	// 카메라 매니저를 통해 카메라 위치와 방향을 가져올 수 있음
	APlayerCameraManager* cameraManager = playerController->PlayerCameraManager;

	if (!IsValid(playerController))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Camera Manager not found!"));
		return;
	}

	// 카메라 컴포넌트를 반환하려면 캐릭터의 카메라 컴포넌트를 직접 가져와야 함
	playerCamera = playerController->GetPawn();
	if (!IsValid(playerCamera))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Active camera is not an ACameraActor."));
		return;
	}
}

void AGoBoard::Run()
{
	ChangeArrowPosition();
}

void AGoBoard::Clear()
{
	isPlay = false;
	isPlayerTurn = false;

	for (auto& stone : stones)
	{
		if (IsValid(stone))
			stone->Destroy();
	}

	stones.clear();

	x = 9;
	y = 9;

	if (action)
	{
		delete action;  // 일반 객체라면 delete 사용
		action = nullptr;
	}

	if (playerCamera == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Player Camera does not exist."));
		return;
	}

	// 플레이어의 뷰 타겟(View Target)을 해당 카메라로 전환
	playerController->SetViewTargetWithBlend(
		playerCamera,								// 새로운 뷰 타겟
		0.0f,										// 블렌드 시간 (0.0초)
		EViewTargetBlendFunction::VTBlend_Linear,	// 블렌드 함수 (선형)
		0.0f,										// 블렌드 지수 (Exponent)
		false										// 기존 뷰 타겟 잠금 여부
	);

	playerMovementComponent->SetMovementMode(EMovementMode::MOVE_Walking);
	playerController->SetIgnoreLookInput(false);
}

void AGoBoard::ChangeArrowPosition()
{
	spawnedArrow->SetActorRelativeLocation
	(
		FVector((y - 9 - CENTER_Y) * STEP_Y,
				(x - 9 - CENTER_X) * STEP_X,
				CENTER_Z)
	);
}

void AGoBoard::PlayerPlace()
{
	// 플레이어 턴이 아니거나 게임을 시작을 하지 않았더라면, 오목 알을 두지 않음
	if (!isPlayerTurn || !isPlay)
		return;

	if (whiteStone == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("White Stone is Nullptr!!"));
		return;
	}

	if (action == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("GoBoardInfo is Nullptr!!"));
		return;
	}

	// 해당 위치에 바둑 돌을 놓을 수 있는지 확인하여 가능하면 생성
	FVector placeRealPosition;
	if (action->PlaceStone(x, y, 2, placeRealPosition))
	{
		// 스폰 파라미터 설정
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		// 블루프린트 클래스에서 액터 생성
		FVector spawnLocation = FVector(0.0f, 0.0f, 0.0f); // 원하는 스폰 위치
		FRotator spawnRotation = FRotator::ZeroRotator;    // 원하는 회전 값

		AActor* spawnStone = GetWorld()->SpawnActor<AActor>(whiteStone, spawnLocation, spawnRotation, SpawnParams);

		// boxComponent에 goBoardMesh를 붙이고 위치 설정
		spawnStone->AttachToComponent(boxComponent, FAttachmentTransformRules::KeepRelativeTransform);
		spawnStone->SetActorRelativeLocation(FVector(placeRealPosition.X, placeRealPosition.Y, placeRealPosition.Z));

		stones.push_back(spawnStone);
		audioComponent->Play();

		isPlayerTurn = false;
		
		if (!action->CheckWin(2))
			AIPlace();

		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Player Win!!"));
			return;
		}
	}
}

void AGoBoard::AIPlace()
{
	if (blackStone == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Black Stone is Nullptr!!"));
		return;
	}

	if (action == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("GoBoardInfo is Nullptr!!"));
		return;
	}

	// 해당 위치에 바둑 돌을 놓을 수 있는지 확인하여 가능하면 생성
	FVector placeRealPosition;
	std::pair<int, int> placeBoradPosition = action->AIPlaceStone();
	if (!action->PlaceStone(placeBoradPosition.first, placeBoradPosition.second, 1, placeRealPosition))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("AI cannot be placed in that location."));
		return;
	}

	// 스폰 파라미터 설정
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	// 블루프린트 클래스에서 액터 생성
	FVector spawnLocation = FVector(0.0f, 0.0f, 0.0f); // 원하는 스폰 위치
	FRotator spawnRotation = FRotator::ZeroRotator;    // 원하는 회전 값

	AActor* spawnStone = GetWorld()->SpawnActor<AActor>(blackStone, spawnLocation, spawnRotation, SpawnParams);

	// boxComponent에 goBoardMesh를 붙이고 위치 설정
	spawnStone->AttachToComponent(boxComponent, FAttachmentTransformRules::KeepRelativeTransform);
	spawnStone->SetActorRelativeLocation(FVector(placeRealPosition.X, placeRealPosition.Y, placeRealPosition.Z));

	stones.push_back(spawnStone);
	audioComponent->Play();

	if (!action->CheckWin(1))
		isPlayerTurn = true;

	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("AI Win!!"));
		return;
	}
}

void AGoBoard::PlayGame()
{
	// 상호작용 거리가 멀거나 이미 게임을 하고 있는 경우
	if (!CheckPlayerIsClose() || isPlay)
		return;

	playerMovementComponent->DisableMovement();
	playerController->SetIgnoreLookInput(true);

	action = new GoGameInfo(whiteStone, blackStone);

	FindPlayerCamera();

	isPlay = true;
	ChangeToGameCamera();
}

void AGoBoard::MoveToUp()
{
	if (y <= 0)
		return;

	y--;
}

void AGoBoard::MoveToDown()
{
	if (y >= 18)
		return;

	y++;
}

void AGoBoard::MoveToLeft()
{
	if (x <= 0)
		return;

	x--;
}

void AGoBoard::MoveToRight()
{
	if (x >= 18)
		return;

	x++;
}