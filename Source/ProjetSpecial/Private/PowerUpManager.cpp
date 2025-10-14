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
	static ConstructorHelpers::FClassFinder<AAbilityPowerUp> AbilityPowerUpBPClassFinder(TEXT("/Game/Blueprints/BP_AbilityPowerUp"));
	if (AbilityPowerUpBPClassFinder.Succeeded())
	{
		AbilityPowerUpClass = AbilityPowerUpBPClassFinder.Class;
	}
	static ConstructorHelpers::FClassFinder<AFoodPickup> FoodPickupBPClassFinder(TEXT("/Game/Blueprints/BP_FoodPickup"));
	if (FoodPickupBPClassFinder.Succeeded())
	{
		FoodPickupClass = FoodPickupBPClassFinder.Class;
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
			if(type.AbilityType != EAbilityPowerUpType::None)
			{
				AAbilityPowerUp* NewAbilityPowerUp = GetWorld()->SpawnActor<AAbilityPowerUp>(AbilityPowerUpClass,Transform,SpawnParameters);
				if(NewAbilityPowerUp)
				{
					NewAbilityPowerUp->SetupTypeValues(type.AbilityType);
				}
			}
			else
			{
				if(type.FoodType != EFoodType::No)
				{
					AFoodPickup* NewFoodPickup = GetWorld()->SpawnActor<AFoodPickup>(FoodPickupClass,Transform,SpawnParameters);
					if(NewFoodPickup)
					{
						NewFoodPickup->SetupValues(type.FoodType);
					}
				}
				else
				{
					APowerUp* newPowerUp = GetWorld()->SpawnActor<APowerUp>(PowerUpClass,Transform,SpawnParameters);
					if(newPowerUp)
					{
						newPowerUp->SetupTypeValues(type.Type,static_cast<bool>(type.Quantity));
					}
				}
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
	int nbDropped = FMath::Max(FMath::RandRange(-1,5),1);
	for(int i = 0; i < nbDropped; i++)
	{
		int randomType = FMath::RandRange(0,Health);
		int ChanceForAll = FMath::RandRange(1,40);
		int ChanceForNegative = FMath::RandRange(1,8);
		int ChanceForFood = FMath::RandRange(1,8);
		int FoodHealValue = FMath::RandRange(1,16);
		int ChanceForAbility = FMath::RandRange(1,25);
		int AbilityType = FMath::RandRange(0,EAbilityPowerUpType::FireBreathing - 1);
		FPowerUpData newType;
		if(ChanceForAbility == 1)
		{
			newType.AbilityType = static_cast<EAbilityPowerUpType>(AbilityType+1);
		}
		else
		{
			if(ChanceForFood == 1)
			{
				if(FoodHealValue == 1 || FoodHealValue == 2 || FoodHealValue == 3 || FoodHealValue == 4 || FoodHealValue == 5 || FoodHealValue == 6 || FoodHealValue == 7)
				{
					newType.FoodType = Fish;
				}
				else
				{
					if(FoodHealValue == 8 || FoodHealValue == 9 || FoodHealValue == 10 || FoodHealValue == 11 || FoodHealValue == 12)
					{
						newType.FoodType = Steak;
					}
					else
					{
						if(FoodHealValue == 13 || FoodHealValue == 14 || FoodHealValue == 15)
						{
							newType.FoodType = Drumstick;
						}
						else
						{
							if(FoodHealValue == 16)
							{
								newType.FoodType  = DragonFruit;
							}
						}
					}
				}
				
			}
			else
			{
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
			}
		}
		
		
		powerUpTypes.Add(newType);
	}
	return powerUpTypes;
}


