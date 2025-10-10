// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUpCrate.h"


#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
APowerUpCrate::APowerUpCrate()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	//RootComponent = BoxComponent;

	//Mesh = CreateDefaultSubobject<UGeometryCollectionComponent>("Mesh");
	//Mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APowerUpCrate::BeginPlay()
{
	Super::BeginPlay();
	
}

void APowerUpCrate::OnHittableObjectHit_Implementation(float damage, AActor* Source,FHitResult Hit)
{
	//IHitableActor::OnHittableObjectHit_Implementation(damage, Source);
	
}

// Called every frame
void APowerUpCrate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

