// Fill out your copyright notice in the Description page of Project Settings.


#include "People.h"

#include "Components/SkeletalMeshComponent.h"

// Sets default values
APeople::APeople()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APeople::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APeople::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

