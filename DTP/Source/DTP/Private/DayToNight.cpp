// Fill out your copyright notice in the Description page of Project Settings.


#include "DayToNight.h"
#include "Components/BoxComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADayToNight::ADayToNight()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	boxComponent->SetBoxExtent(FVector(500.0f, 500.0f, 500.0f));
	SetRootComponent(boxComponent);

	oldClockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Old Clock Mesh"));
	oldClockMesh->SetupAttachment(boxComponent);
}

// Called when the game starts or when spawned
void ADayToNight::BeginPlay()
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

	EnableInput(playerController);
	playerInputComponent->BindAction(TEXT("Interaction"), IE_Pressed, this, &ADayToNight::ChangeTime);
}

void ADayToNight::ChangeTime()
{
	// ��ȣ�ۿ� �Ÿ��� �ְų� �̹� �ٲ�� �ִ� ���
	if (!CheckPlayerIsClose() || isTimeChange)
		return;

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("SUCCEED"));

	// ���� �ð��� �ٲ�� �ִ��� ���θ� ������ �ٲٰ� �㳷 �ð��� �ٲ�
	isTimeChange = true;
	isDay = !isDay;
}

bool ADayToNight::CheckPlayerIsClose()
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

// Called every frame
void ADayToNight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	hasClosePlayer = CheckPlayerIsClose();
}