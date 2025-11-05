// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ExplorationGameState.generated.h"

/**
 * 
 */
UCLASS()
class PROJETSPECIAL_API AExplorationGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	//UPROPERTY(ReplicatedUsing=OnRep_TimerEndTime)
	float TimerEndTime;
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnGameTimeElapsed(float EndTime);
	//UFUNCTION()
	//void OnRep_TimerEndTime();
};
