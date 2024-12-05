// Fill out your copyright notice in the Description page of Project Settings.


#include "GoBoard.h"
#include "GoGameInfo.h"
#include "Camera/CameraActor.h"
#include "Components/BoxComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
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

	// arrow�� ������ �������Ʈ Ŭ������ ��ȿ���� Ȯ��
	if (arrow == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("arrow is not set!"));
		return;
	}

	// ���� �Ķ���� ����
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	// �������Ʈ Ŭ�������� ���� ����
	FVector spawnLocation = FVector(0.0f, 0.0f, 0.0f); // ���ϴ� ���� ��ġ
	FRotator spawnRotation = FRotator::ZeroRotator;    // ���ϴ� ȸ�� ��

	spawnedArrow = GetWorld()->SpawnActor<AActor>(arrow, spawnLocation, spawnRotation, SpawnParams);

	// boxComponent�� goBoardMesh�� ���̰� ��ġ ����
	spawnedArrow->AttachToComponent(boxComponent, FAttachmentTransformRules::KeepRelativeTransform);
	spawnedArrow->SetActorRelativeLocation(FVector(0.0f, 0.0f, CENTER_Y));

	EnableInput(playerController);
	playerInputComponent->BindAction(TEXT("Interaction"), IE_Pressed, this, &AGoBoard::PlayGame);
	playerInputComponent->BindAction(TEXT("Up"), IE_Pressed, this, &AGoBoard::MoveToUp);
	playerInputComponent->BindAction(TEXT("Down"), IE_Pressed, this, &AGoBoard::MoveToDown);
	playerInputComponent->BindAction(TEXT("Left"), IE_Pressed, this, &AGoBoard::MoveToLeft);
	playerInputComponent->BindAction(TEXT("Right"), IE_Pressed, this, &AGoBoard::MoveToRight);
	playerInputComponent->BindAction(TEXT("Place"), IE_Pressed, this, &AGoBoard::PlayerPlace);

	playerAction = new GoGameInfo(whiteStone, blackStone);
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

	// �÷��̾�� �ش� ������Ʈ ��ġ�� ����
	FVector position = GetActorLocation();
	FVector playerPosition = player->GetActorLocation();

	// �÷��̾�� �ش� ������Ʈ �Ÿ��� ����
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

	// �÷��̾��� �� Ÿ��(View Target)�� �ش� ī�޶�� ��ȯ
	playerController->SetViewTargetWithBlend(
		startCamera, // ���ο� �� Ÿ��
		0.0f,        // ���� �ð� (0.0��)
		EViewTargetBlendFunction::VTBlend_Linear, // ���� �Լ� (����)
		0.0f,        // ���� ���� (Exponent)
		false        // ���� �� Ÿ�� ��� ����
	);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Camera Change Succeed!!"));
}

void AGoBoard::Run()
{
	ChangeArrowPosition();
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
	if (whiteStone == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("White Stone is Nullptr!!"));
		return;
	}

	//if (blackStone == nullptr)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Black Stone is Nullptr!!"));
	//	return;
	//}

	if (playerAction == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("GoBoardInfo is Nullptr!!"));
		return;
	}

	// �ش� ��ġ�� �ٵ� ���� ���� �� �ִ��� Ȯ���Ͽ� �����ϸ� ����
	FVector placeRealPosition;
	if (playerAction->PlaceStone(x, y, 2, placeRealPosition))
	{
		// ���� �Ķ���� ����
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		// �������Ʈ Ŭ�������� ���� ����
		FVector spawnLocation = FVector(0.0f, 0.0f, 0.0f); // ���ϴ� ���� ��ġ
		FRotator spawnRotation = FRotator::ZeroRotator;    // ���ϴ� ȸ�� ��

		AActor* spawnStone = GetWorld()->SpawnActor<AActor>(whiteStone, spawnLocation, spawnRotation, SpawnParams);

		// boxComponent�� goBoardMesh�� ���̰� ��ġ ����
		spawnStone->AttachToComponent(boxComponent, FAttachmentTransformRules::KeepRelativeTransform);
		spawnStone->SetActorRelativeLocation(FVector(placeRealPosition.X, placeRealPosition.Y, placeRealPosition.Z));

		stones.push_back(spawnStone);
	}
}

void AGoBoard::PlayGame()
{
	// ��ȣ�ۿ� �Ÿ��� �ְų� �̹� ������ �ϰ� �ִ� ���
	if (!CheckPlayerIsClose() || isPlay)
		return;

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