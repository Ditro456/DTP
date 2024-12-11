// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatWidget.h"

// Sets default values
AChatWidget::AChatWidget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AChatWidget::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChatWidget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}