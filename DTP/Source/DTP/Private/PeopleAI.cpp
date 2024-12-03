// Fill out your copyright notice in the Description page of Project Settings.


#include "PeopleAI.h"
#include "People.h"
#include "NavigationSystem.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Navigation/PathFollowingComponent.h"

void APeopleAI::OnMoveCompleted(FAIRequestID requestID, const FPathFollowingResult& result)
{
	Super::OnMoveCompleted(requestID, result);

	// 최소 대기 시간과 최대 대기 시간 사이에서 랜덤 대기 시간 선택
	float waitTime = FMath::RandRange(minWaitTime, maxWaitTime);

	isWait = true;

	// 타이머 설정 로그 추가
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, *FString::Printf(TEXT("Setting Timer for %f seconds"), waitTime));

	// 대기 시간 후에 StartSearchPlayer 호출
	GetWorld()->GetTimerManager().SetTimer(waitMoveTimer, this, &APeopleAI::ChangeWait, waitTime, false);
}

void APeopleAI::BeginPlay()
{
	Super::BeginPlay();

	navArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
	movementComponent = GetPawn()->FindComponentByClass<UCharacterMovementComponent>();

	// 최대 이동 속력을 저장함
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

	float accelerationRate = maxSpeed / increaseToMaxSpeedTime; // 초당 증가할 속도
	float currentSpeed = movementComponent->MaxWalkSpeed;		// 현재 이동 속도

	currentSpeed = FMath::Min(currentSpeed + accelerationRate * deltaSecond, maxSpeed);
	movementComponent->MaxWalkSpeed = currentSpeed;
}

void APeopleAI::LookAtLocation(FVector targetLocation)
{
	APawn* monster = GetPawn();
	if (monster == nullptr)
		return;

	// 몬스터의 이동 방향 벡터를 가져옴
	FVector monsterVelocity = monster->GetVelocity();

	// 이동 방향이 없으면 회전하지 않음
	if (monsterVelocity.IsNearlyZero())
		return;

	// Z축(상하 축)의 영향을 제거하고, 방향 벡터를 정규화
	FVector direction = monsterVelocity.GetSafeNormal();
	direction.Z = 0.0f;

	// 목표 회전 값(이동 방향)을 계산
	FRotator targetRotation = FRotationMatrix::MakeFromX(direction).Rotator();
	FRotator currentRotation = monster->GetActorRotation();

	// 현재 회전 값에서 목표 회전 값으로 선형 보간하여 회전
	FRotator newRotation = FMath::RInterpTo(currentRotation, targetRotation, GetWorld()->GetDeltaSeconds(), rotationSpeed);
	monster->SetActorRotation(newRotation);
}

void APeopleAI::GenerateRandomSearchLocation()
{
	FNavLocation resultLocation;

	// 10000.0f 범위의 랜덤한 위치를 정함
	bool isSucceed = navArea->GetRandomReachablePointInRadius(GetPawn()->GetActorLocation(), 10000.0f, resultLocation);

	if (!isSucceed)
		return;
	
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, *FString::Printf(TEXT("Random Location: %s"), *toLocation.ToString()));

	// 랜덤한 위치로 지정
	toLocation = resultLocation.Location;
}