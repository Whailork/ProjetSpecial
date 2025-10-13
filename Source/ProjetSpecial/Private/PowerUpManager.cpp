// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUpManager.h"

#include "PowerUpComponent.h"

UPowerUpManager::UPowerUpManager()
{
	static ConstructorHelpers::FClassFinder<APowerUp> PowerUpBPClassFinder(TEXT("/Game/Blueprints/BP_PowerUp"));
	if (PowerUpBPClassFinder.Succeeded())
	{
		PowerUpClass = PowerUpBPClassFinder.Class;
	}
	/*static ConstructorHelpers::FClassFinder<APowerUp> CrateBPClassFinder(TEXT("/Game/Blueprints/BP_MyActor.BP_MyActor_C"));
	if (CrateBPClassFinder.Succeeded())
	{
		PowerUpClass = CrateBPClassFinder.Class;
	}*/
}

void UPowerUpManager::SpawnPowerUps(TArray<FPowerUpData> powerUpTypes,const FVector AroundLocation)
{
	for (auto type : powerUpTypes)
	{
		const FActorSpawnParameters SpawnParameters;
		
		FTransform Transform;
		Transform.SetLocation(AroundLocation);
		Transform.SetRotation(FQuat::Identity);
		if(GetWorld())
		{
			APowerUp* newPowerUp = GetWorld()->SpawnActor<APowerUp>(PowerUpClass,Transform,SpawnParameters);
			if(newPowerUp)
			{
				newPowerUp->SetupTypeValues(type.Type,static_cast<bool>(type.Quantity));
			}
			
		}
		
	}
}

void UPowerUpManager::SpawnCrate(ACrateSpawner* CrateSpawner)
{
}

TArray<FPowerUpData> UPowerUpManager::GeneratePowerUpDrops()
{
	TArray<FPowerUpData> powerUpTypes;
	int nbDropped = FMath::Max(FMath::RandRange(-2,5),2);
	for(int i = 0; i < nbDropped; i++)
	{
		int randomType = FMath::RandRange(0,Health);
		int ChanceForAll = FMath::RandRange(1,20);
		int ChanceForNegative = FMath::RandRange(1,8);
		FPowerUpData newType;
		if(ChanceForNegative == 1)
		{
			newType.Quantity = 1;
		}
		else
		{
			newType.Quantity = 0;
		}
		if(ChanceForAll == 1)
		{
			newType.Type = All;
		
		}
		else
		{
			newType.Type = static_cast<EPowerUpType>(randomType);
		}
		
		powerUpTypes.Add(newType);
	}
	return powerUpTypes;
}


