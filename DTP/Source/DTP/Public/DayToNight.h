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
	void ChangeTime();			// �ð��� �ٲٴ� �޼ҵ�

	bool CheckPlayerIsClose();	// �÷��̾ �ð�� ������� Ȯ���ϴ� �޼ҵ�
	

	class AActor* player;
	class APlayerController* playerController;
};