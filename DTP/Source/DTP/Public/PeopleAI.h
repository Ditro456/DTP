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
	float minWaitTime = 1.0f;					// �ּ� ��� �ð� (��)

	UPROPERTY(EditAnywhere, Category = "AI")
	float maxWaitTime = 3.0f;					// �ִ� ��� �ð� (��)

	UPROPERTY(EditAnywhere, Category = "AI")
	float rotationSpeed = 5.0f; // ȸ�� �ӵ� (�ʴ� ��)

protected:
	void BeginPlay() override;
	void Tick(float deltaSeconds);

private:
	void GenerateRandomSearchLocation();
	void ChangeWait();

	void StartMoveSpeed();
	void IncreaseMoveSpeed(float deltaSecond);
	void LookAtLocation(FVector targetLocation);

	class UNavigationSystemV1* navArea;						// �׺���̼� �ý���
	class UCharacterMovementComponent* movementComponent;	// �̵� ���� ������Ʈ

	FTimerHandle waitMoveTimer;								// ���� �̵� Ÿ�Ӹ�

	FVector toLocation = FVector();							// ����� �̵��� ��ġ

	float maxSpeed;											// ����� �ִ� �̵� �ӵ�
	float increaseToMaxSpeedTime = 0.5f;					// �ִ� �ӷ±��� �����ϴµ� �ɸ��� �ð�
	
	bool isWait;
};
