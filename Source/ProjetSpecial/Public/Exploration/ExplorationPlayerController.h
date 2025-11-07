// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjetSpecialPlayerController.h"
#include "GameFramework/PlayerController.h"
#include "ExplorationPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJETSPECIAL_API AExplorationPlayerController : public AProjetSpecialPlayerController
{
	GENERATED_BODY()
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintNativeEvent)
	void OnSwitchToTrial(FName TrialName);
};
