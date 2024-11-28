// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "People.generated.h"

UCLASS()
class DTP_API APeople : public ACharacter
{
	GENERATED_BODY()
	
public:	
	APeople();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;


private:

};
