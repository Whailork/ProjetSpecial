// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FoodPickup.h"
#include "PowerUp.h"
#include "PowerUpComponent.h"
#include "Subsystems/WorldSubsystem.h"
#include "PowerUpManager.generated.h"

/**
 * 
 */


USTRUCT(BlueprintType)
struct FPickupDataRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickupData")
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickupData")
	UTexture2D* PickupSprite;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickupData")
	UTexture2D* NegativeSprite;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickupData")
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickupData")
	float Value;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickupData")
	FColor TextColor;
	
};

UCLASS(BlueprintType)
class PROJETSPECIAL_API UPowerUpManager : public UWorldSubsystem
{
	GENERATED_BODY()
	UPowerUpManager();
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<APowerUp> PowerUpClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AAbilityPowerUp> AbilityPowerUpClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AFoodPickup> FoodPickupClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<AActor>> JarClasses; 
	UFUNCTION(BlueprintCallable)
	void SpawnPowerUps(TArray<FPowerUpData> powerUpTypes,FVector AroundLocation);
	UFUNCTION(BlueprintCallable)
	void SpawnCrate(FVector SpawnLocation);
	UFUNCTION(BlueprintCallable)
	TArray<FPowerUpData> GeneratePowerUpDrops();
};
