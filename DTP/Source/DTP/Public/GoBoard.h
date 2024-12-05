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
	class ACameraActor* startCamera;			// ���� ī�޶� ������Ʈ

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
	bool CheckPlayerIsClose();	// �÷��̾ �����ǰ� ������� Ȯ���ϴ� �޼ҵ�
	void ChangeToGameCamera();	// �÷��̾�� ���� ī�޶�� �̵�
	void Run();					// ���� �÷���

	void PlayGame();
	void ChangeArrowPosition();	// ȭ�� ��ġ ����
	void PlayerPlace();			// �÷��̾� �α�

	void MoveToUp();
	void MoveToDown();
	void MoveToLeft();
	void MoveToRight();

	class AActor* player;
	class APlayerController* playerController;
	class AActor* spawnedArrow;

	class GoGameInfo* playerAction;

	std::vector<AActor*> stones;

	int x, y;
};