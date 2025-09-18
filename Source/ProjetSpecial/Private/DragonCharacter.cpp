// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/DragonCharacter.h"

#include "EnhancedInputComponent.h"
#include "ProjetSpecial.h"

// Sets default values
ADragonCharacter::ADragonCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	

}

// Called when the game starts or when spawned
void ADragonCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADragonCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADragonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}

