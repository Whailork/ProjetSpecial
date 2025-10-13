// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUpComponent.h"

#include "PowerUpManager.h"
#include "Algo/ForEach.h"


// Sets default values for this component's properties
UPowerUpComponent::UPowerUpComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UPowerUpComponent::AddPowerUp(EPowerUpType type, bool isNegative)
{
	
	for(int i = 0; i < PowerUps.Num();i++)
	{
		if(PowerUps[i].Type == type)
		{
			FPowerUpData newData;
			int LastQuantity = PowerUps[i].Quantity;
			if(isNegative)
			{
				newData = FPowerUpData(PowerUps[i].Quantity - 1,type);
			}
			else
			{
				newData = FPowerUpData(PowerUps[i].Quantity + 1,type);
			}
			if(newData.Quantity == 0)
			{
				PowerUps.RemoveAt(i);
			}
			else
			{
				PowerUps[i] = newData;
			}
			
			PowerUpAddedDelegate.Broadcast(newData,LastQuantity);
			return;
		}
	}
	int LastQuantity = 0;
	FPowerUpData newData;
	if(isNegative)
	{
		newData = FPowerUpData(-1,type);
	}
	else
	{
		newData = FPowerUpData(1,type);
	}
	
	PowerUps.Add(newData);
	PowerUpAddedDelegate.Broadcast(newData,LastQuantity);
	
}

void UPowerUpComponent::AddAbilityPowerUp(EAbilityPowerUpType AbilityType)
{
	ActiveAbility = AbilityType;
	AbilityActivatedDelegate.Broadcast(AbilityType);
}

void UPowerUpComponent::DropPowerUps(int number)
{
	TArray<FPowerUpData> PowerUpsToDrop;
	TArray<EPowerUpType> AvailableTypes;

	for(int i = 0; i < number;i++)
	{
		AvailableTypes.Empty();
		for (auto powerUp : PowerUps)
		{
			if(powerUp.Quantity > 0)
			{
				AvailableTypes.Add(powerUp.Type);
			}
		}
		if(!AvailableTypes.IsEmpty())
		{
			int typeRandom = FMath::RandRange(0,AvailableTypes.Num()-1);
			EPowerUpType newDataType = AvailableTypes[typeRandom];

			PowerUpsToDrop.Add(FPowerUpData(0,newDataType));

			AddPowerUp(newDataType,true);
			
		}
	}
	if(PowerUpsToDrop.IsEmpty())
	{
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red,FString("No PowerUp to drop"));
		
	}
	else
	{
		
		GetWorld()->GetSubsystem<UPowerUpManager>()->SpawnPowerUps(PowerUpsToDrop,GetOwner()->GetActorLocation());
	}
}

// Called when the game starts
void UPowerUpComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPowerUpComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

