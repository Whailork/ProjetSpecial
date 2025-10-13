// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityPowerUp.h"

#include "PowerUpComponent.h"
#include "ProjetSpecialCharacter.h"
#include "Components/BoxComponent.h"


// Sets default values
AAbilityPowerUp::AAbilityPowerUp()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	
	RootComponent = BoxCollision;

	AppearanceWidget = CreateDefaultSubobject<UWidgetComponent>("AppearanceWidget");
	AppearanceWidget->SetupAttachment(RootComponent);

	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
}

void AAbilityPowerUp::SetCollisions()
{
	BoxCollision->SetCollisionResponseToAllChannels(ECR_Block);
	BoxCollision->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);
	BoxCollision->SetCollisionResponseToChannel(ECC_Camera,ECR_Overlap);
}

void AAbilityPowerUp::Despawn()
{
	StartDespawnAnim = true;
}

void AAbilityPowerUp::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(auto PowerUpComp = OtherActor->GetComponentByClass<UPowerUpComponent>())
	{
		if(auto Character =  Cast<AProjetSpecialCharacter>(OtherActor))
		{
			if(!Character->bIsDead)
			{
				PowerUpComp->AddAbilityPowerUp(Type);
				this->Destroy();
			}
		}
		else
		{
			PowerUpComp->AddAbilityPowerUp(Type);
			this->Destroy();
		}
		
	}
}

void AAbilityPowerUp::SetupTypeValues_Implementation(EAbilityPowerUpType typeValue)
{
	Type = typeValue;
}

// Called when the game starts or when spawned
void AAbilityPowerUp::BeginPlay()
{
	Super::BeginPlay();
	BoxCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	GetWorldTimerManager().SetTimer(SetCollisionTimerHandle,this,&AAbilityPowerUp::SetCollisions,0.5);
	GetWorldTimerManager().SetTimer(DespawnTimerHandle,this,&AAbilityPowerUp::Despawn,DespawnDelay);
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this,&AAbilityPowerUp::OnOverlap);
	
}

// Called every frame
void AAbilityPowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

