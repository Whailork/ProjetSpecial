// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ExplorationGameState.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerReadyForTrialChanged,int32,NbPlayersReady);
UCLASS()
class PROJETSPECIAL_API AExplorationGameState : public AGameStateBase
{
	GENERATED_BODY()

protected:
	int NbPlayers;
	int NbPlayersReadyForTrial;
public:
	//UPROPERTY(ReplicatedUsing=OnRep_TimerEndTime)
	float TimerEndTime;
	UPROPERTY(BlueprintAssignable)
	FOnPlayerReadyForTrialChanged OnPlayerReadyForTrialChangedDelegate;

	UFUNCTION()
	void OnPlayerLoggedIn(APlayerController* newPlayer);
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void PlayerReady();
	UFUNCTION(BlueprintCallable)
	void PlayerNotReady();
	UFUNCTION(BlueprintCallable)
	int GetNbPlayers();

	

	//UFUNCTION()
	//void OnRep_TimerEndTime();
};
