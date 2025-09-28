// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUp.h"

#include "PowerUpComponent.h"


// Sets default values
APowerUp::APowerUp()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	RootComponent = BoxCollision;

	AppearanceWidget = CreateDefaultSubobject<UWidgetComponent>("AppearanceWidget");
	AppearanceWidget->SetupAttachment(RootComponent);
}

void APowerUp::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(auto PowerUpComp = OtherActor->GetComponentByClass<UPowerUpComponent>())
	{
		PowerUpComp->AddPowerUp(Type,IsNegative);
	}
	this->Destroy();
}

// Called when the game starts or when spawned
void APowerUp::BeginPlay()
{
	Super::BeginPlay();
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this,&APowerUp::OnOverlap);
	
}

// Called every frame
void APowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

