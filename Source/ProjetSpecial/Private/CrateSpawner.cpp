// Fill out your copyright notice in the Description page of Project Settings.


#include "CrateSpawner.h"


// Sets default values
ACrateSpawner::ACrateSpawner()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACrateSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACrateSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACrateSpawner::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

