// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ExplorationGameMode.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSwitchToTrial,FName,TrialName);
UCLASS()
class PROJETSPECIAL_API AExplorationGameMode : public AGameModeBase
{
	GENERATED_BODY()
	virtual void BeginPlay() override;

public:
	//game time is in seconds
	UPROPERTY(BlueprintReadOnly)
	float GameTime = 1200;
	FOnSwitchToTrial OnSwitchToTrialDelegate;
	FName ChosenTrial;
	
	UPROPERTY(EditDefaultsOnly)
	UDataTable* TrialsDataTable;
	
	UFUNCTION()
	void OnGameTimeElapsed(float EndTime);
	UFUNCTION()
	void TravelToTrial();
};
