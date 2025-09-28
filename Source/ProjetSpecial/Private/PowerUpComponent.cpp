// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUpComponent.h"

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
			
			PowerUps[i] = newData;
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

