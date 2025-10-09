// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUpManager.h"

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

void UPowerUpManager::SpawnPowerUps(TArray<TEnumAsByte<EPowerUpType>> powerUpTypes,const FVector AroundLocation)
{
	for (auto type : powerUpTypes)
	{
		//add code to check for surrounding locations
		const FActorSpawnParameters SpawnParameters;
		
		FTransform Transform;
		Transform.SetLocation(AroundLocation);
		Transform.SetRotation(FQuat::Identity);
		if(GetWorld())
		{
			APowerUp* newPowerUp = GetWorld()->SpawnActor<APowerUp>(PowerUpClass,Transform,SpawnParameters);
			if(newPowerUp)
			{
				newPowerUp->Type = type;
			}
			
		}
		
	}
}
