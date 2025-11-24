// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerUpComponent.h"
#include "ProjetSpecialCharacter.h"
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
	TArray<FSKinData> SavedSkins;
public:
	UFUNCTION(BlueprintCallable)
	void SavePowerUpDatas();
	UFUNCTION(BlueprintCallable)
	void ClearSavedPowerUpDatas();
	UFUNCTION(BlueprintCallable)
	TArray<FPowerUpData> GetPowerUpDatas(int LocalPlayerNumber);
	void AssignSavedPowerUps(TArray<APlayerController*> Players);
	UFUNCTION(BlueprintCallable)
	void SaveSkinDatas(bool FromLobby);
	void AssingSavedSkins(TArray<APlayerController*> Players);
	FSKinData GetSkinData(int LocalPlayerNumber);
	
};
