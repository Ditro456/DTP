// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <vector>

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GoBoard.generated.h"


UCLASS()
class DTP_API AGoBoard : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGoBoard();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* boxComponent;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* goBoardMesh;

	UPROPERTY(EditAnywhere)
	class UClass* arrow;

	UPROPERTY(EditAnywhere)
	class UClass* whiteStone;

	UPROPERTY(EditAnywhere)
	class UClass* blackStone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	class ACameraActor* startCamera;			// 시작 카메라 오브젝트

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "State")
	class UAudioComponent* audioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	float interactionDistance = 600.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	bool isPlay = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	bool hasClosePlayer = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	bool CheckPlayerIsClose();	// 플레이어가 오목판과 가까운지 확인하는 메소드
	void ChangeToGameCamera();	// 플레이어에서 영상 카메라로 이동
	void FindPlayerCamera();	// 플레이어 카메라를 찾는 메소드
	void Run();					// 게임 플레이
	void Clear();				// 게임 끝내기

	void PlayGame();
	void ChangeArrowPosition();	// 화살 위치 변경
	void PlayerPlace();			// 플레이어 두기
	void AIPlace();

	void MoveToUp();
	void MoveToDown();
	void MoveToLeft();
	void MoveToRight();

	class AActor* player;											// 플레이어 Actor
	class APlayerController* playerController;
	class UCharacterMovementComponent* playerMovementComponent;		// 플레이어 이동관련 컴포넌트
	class AActor* playerCamera;										// 플레이어 카메라
	class AActor* spawnedArrow;

	class GoGameInfo* action;

	std::vector<AActor*> stones;				// 현재 바둑 판에 있는 바둑 돌

	int x, y;
	bool isPlayerTurn = false;
};