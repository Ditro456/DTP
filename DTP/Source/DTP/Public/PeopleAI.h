// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PeopleAI.generated.h"

/**
 * 
 */
UCLASS()
class DTP_API APeopleAI : public AAIController
{
	GENERATED_BODY()

public:
	void OnMoveCompleted(FAIRequestID requestID, const FPathFollowingResult& result) override;

	// ==============================================================
	//							Public Variable
	// ==============================================================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float maxWalkSpeed = 150.0f;

	UPROPERTY(EditAnywhere, Category = "AI")
	float minWaitTime = 1.0f;					// 최소 대기 시간 (초)

	UPROPERTY(EditAnywhere, Category = "AI")
	float maxWaitTime = 3.0f;					// 최대 대기 시간 (초)

	UPROPERTY(EditAnywhere, Category = "AI")
	float rotationSpeed = 5.0f; // 회전 속도 (초당 도)

protected:
	void BeginPlay() override;
	void Tick(float deltaSeconds);

private:
	void GenerateRandomSearchLocation();
	void ChangeWait();

	void StartMoveSpeed();
	void IncreaseMoveSpeed(float deltaSecond);
	void LookAtLocation(FVector targetLocation);

	class UNavigationSystemV1* navArea;						// 네비게이션 시스템
	class UCharacterMovementComponent* movementComponent;	// 이동 관련 컴포넌트

	FTimerHandle waitMoveTimer;								// 다음 이동 타임머

	FVector toLocation = FVector();							// 사람이 이동할 위치

	float maxSpeed;											// 사람의 최대 이동 속도
	float increaseToMaxSpeedTime = 0.5f;					// 최대 속력까지 증가하는데 걸리는 시간
	
	bool isWait;
};
