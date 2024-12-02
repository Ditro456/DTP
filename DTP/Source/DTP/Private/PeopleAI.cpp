// Fill out your copyright notice in the Description page of Project Settings.


#include "PeopleAI.h"
#include "People.h"
#include "NavigationSystem.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Navigation/PathFollowingComponent.h"

void APeopleAI::OnMoveCompleted(FAIRequestID requestID, const FPathFollowingResult& result)
{
	Super::OnMoveCompleted(requestID, result);

	// �ּ� ��� �ð��� �ִ� ��� �ð� ���̿��� ���� ��� �ð� ����
	float waitTime = FMath::RandRange(minWaitTime, maxWaitTime);

	isWait = true;

	// Ÿ�̸� ���� �α� �߰�
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, *FString::Printf(TEXT("Setting Timer for %f seconds"), waitTime));

	// ��� �ð� �Ŀ� StartSearchPlayer ȣ��
	GetWorld()->GetTimerManager().SetTimer(waitMoveTimer, this, &APeopleAI::ChangeWait, waitTime, false);
}

void APeopleAI::BeginPlay()
{
	Super::BeginPlay();

	navArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
	movementComponent = GetPawn()->FindComponentByClass<UCharacterMovementComponent>();

	// �ִ� �̵� �ӷ��� ������
	maxSpeed = maxWalkSpeed;

	GenerateRandomSearchLocation();
	StartMoveSpeed();
	MoveTo(toLocation);
}

void APeopleAI::Tick(float deltaSeconds)
{
	IncreaseMoveSpeed(deltaSeconds);
	LookAtLocation(toLocation);
}

void APeopleAI::ChangeWait()
{
	isWait = false;

	GenerateRandomSearchLocation();
	StartMoveSpeed();
	MoveTo(toLocation);
}

void APeopleAI::StartMoveSpeed()
{
	movementComponent->MaxWalkSpeed = 0.0f;
}

void APeopleAI::IncreaseMoveSpeed(float deltaSecond)
{
	if (movementComponent->MaxWalkSpeed >= maxSpeed)
		return;

	float accelerationRate = maxSpeed / increaseToMaxSpeedTime; // �ʴ� ������ �ӵ�
	float currentSpeed = movementComponent->MaxWalkSpeed;		// ���� �̵� �ӵ�

	currentSpeed = FMath::Min(currentSpeed + accelerationRate * deltaSecond, maxSpeed);
	movementComponent->MaxWalkSpeed = currentSpeed;
}

void APeopleAI::LookAtLocation(FVector targetLocation)
{
	APawn* monster = GetPawn();
	if (monster == nullptr)
		return;

	// ������ �̵� ���� ���͸� ������
	FVector monsterVelocity = monster->GetVelocity();

	// �̵� ������ ������ ȸ������ ����
	if (monsterVelocity.IsNearlyZero())
		return;

	// Z��(���� ��)�� ������ �����ϰ�, ���� ���͸� ����ȭ
	FVector direction = monsterVelocity.GetSafeNormal();
	direction.Z = 0.0f;

	// ��ǥ ȸ�� ��(�̵� ����)�� ���
	FRotator targetRotation = FRotationMatrix::MakeFromX(direction).Rotator();
	FRotator currentRotation = monster->GetActorRotation();

	// ���� ȸ�� ������ ��ǥ ȸ�� ������ ���� �����Ͽ� ȸ��
	FRotator newRotation = FMath::RInterpTo(currentRotation, targetRotation, GetWorld()->GetDeltaSeconds(), rotationSpeed);
	monster->SetActorRotation(newRotation);
}

void APeopleAI::GenerateRandomSearchLocation()
{
	FNavLocation resultLocation;

	// 10000.0f ������ ������ ��ġ�� ����
	bool isSucceed = navArea->GetRandomReachablePointInRadius(GetPawn()->GetActorLocation(), 10000.0f, resultLocation);

	if (!isSucceed)
		return;
	
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, *FString::Printf(TEXT("Random Location: %s"), *toLocation.ToString()));

	// ������ ��ġ�� ����
	toLocation = resultLocation.Location;
}