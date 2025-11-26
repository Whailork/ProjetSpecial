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
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> TrialLevelRef;
	//game time is in seconds
	UPROPERTY(BlueprintReadOnly,EditDefaultsOnly)
	float GameTime = 90;
	FOnSwitchToTrial OnSwitchToTrialDelegate;
	FName ChosenTrial;
	
	UPROPERTY(EditDefaultsOnly)
	UDataTable* TrialsDataTable;
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<AActor> ExplorationSpawn;
	UFUNCTION()
	void OnGameTimeElapsed(float EndTime);
	UFUNCTION()
	void TravelToTrial();
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
};
