// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerUp.h"
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
	void SpawnPowerUps(TArray<TEnumAsByte<EPowerUpType>> powerUpTypes,FVector AroundLocation);
};
