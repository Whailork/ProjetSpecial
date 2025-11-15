// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerUpComponent.h"
#include "Engine/GameInstance.h"
#include "ProjetSpecialGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJETSPECIAL_API UProjetSpecialGameInstance : public UGameInstance
{
	GENERATED_BODY()

	TArray<TArray<FPowerUpData>> SavedPowerUps;
public:
	UFUNCTION(BlueprintCallable)
	TArray<FPowerUpData> GetPowerUpDatas(int LocalPlayerNumber);
	void AssignSavedPowerUps(TArray<APlayerController*> Players);
	
};
