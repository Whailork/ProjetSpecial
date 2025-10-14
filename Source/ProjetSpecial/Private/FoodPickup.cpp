// Fill out your copyright notice in the Description page of Project Settings.


#include "FoodPickup.h"

#include "PowerUpComponent.h"
#include "PowerUpManager.h"
#include "ProjetSpecialCharacter.h"


// Sets default values
AFoodPickup::AFoodPickup()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	
	RootComponent = BoxCollision;

	AppearanceWidget = CreateDefaultSubobject<UWidgetComponent>("AppearanceWidget");
	AppearanceWidget->SetupAttachment(RootComponent);

	SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
}

void AFoodPickup::SetCollisions()
{
	BoxCollision->SetCollisionResponseToAllChannels(ECR_Block);
	BoxCollision->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);
	BoxCollision->SetCollisionResponseToChannel(ECC_Camera,ECR_Overlap);
}

void AFoodPickup::Despawn()
{
	StartDespawnAnim = true;
}

void AFoodPickup::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(auto PowerUpComp = OtherActor->GetComponentByClass<UPowerUpComponent>())
	{
		if(auto Character =  Cast<AProjetSpecialCharacter>(OtherActor))
		{
			if(!Character->bIsDead)
			{
				PowerUpComp->AddFoodPickup(Type,HealPercentage);
				this->Destroy();
			}
		}
		else
		{
			PowerUpComp->AddFoodPickup(Type,HealPercentage);
			this->Destroy();
		}
		
	}
}

void AFoodPickup::SetupValues_Implementation(EFoodType type)
{
	Type = type;
	FPickupDataRow* pickupRow = PickupDataTable->FindRow<FPickupDataRow>(StaticEnum<EFoodType>()->GetNameByValue(type),TEXT("Row not found"));
	if(pickupRow)
	{
		HealPercentage = pickupRow->Value;
	}
}

// Called when the game starts or when spawned
void AFoodPickup::BeginPlay()
{
	Super::BeginPlay();
	BoxCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	GetWorldTimerManager().SetTimer(SetCollisionTimerHandle,this,&AFoodPickup::SetCollisions,0.5);
	GetWorldTimerManager().SetTimer(DespawnTimerHandle,this,&AFoodPickup::Despawn,DespawnDelay);
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this,&AFoodPickup::OnOverlap);
	
}

// Called every frame
void AFoodPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

