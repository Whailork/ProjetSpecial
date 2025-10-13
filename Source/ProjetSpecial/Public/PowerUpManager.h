// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CrateSpawner.h"
#include "PowerUp.h"
#include "PowerUpComponent.h"
#include "Subsystems/WorldSubsystem.h"
#include "PowerUpManager.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class PROJETSPECIAL_API UPowerUpManager : public UWorldSubsystem
{
	GENERATED_BODY()
	UPowerUpManager();
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<APowerUp> PowerUpClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> CrateClass; 
	UFUNCTION(BlueprintCallable)
	void SpawnPowerUps(TArray<FPowerUpData> powerUpTypes,FVector AroundLocation);
	UFUNCTION(BlueprintCallable)
	void SpawnCrate(ACrateSpawner* CrateSpawner);
	UFUNCTION(BlueprintCallable)
	TArray<FPowerUpData> GeneratePowerUpDrops();
};
