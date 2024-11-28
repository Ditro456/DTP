// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DayToNight.generated.h"

UCLASS()
class DTP_API ADayToNight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADayToNight();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* oldClockMesh;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* boxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	float interactionDistance = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	bool isDay = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	bool isTimeChange = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void ChangeTime();			// 시간을 바꾸는 메소드

	bool CheckPlayerIsClose();	// 플레이어가 시계와 가까운지 확인하는 메소드
	

	class AActor* player;
	class APlayerController* playerController;
};