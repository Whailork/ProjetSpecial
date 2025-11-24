// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "TrialGameStateBase.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTrialFinished);

UCLASS()
class PROJETSPECIAL_API ATrialGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

	virtual void BeginPlay() override;
public:
	UPROPERTY(BlueprintAssignable)
	FOnTrialFinished TrialFinishedDelegate;

	int NbPlayers;

	UFUNCTION()
	void OnPlayerLoggedIn(APlayerController* newPlayer);
	UFUNCTION(BlueprintCallable)
	virtual int32 GetFinishScore(APlayerController* Player);
	UFUNCTION()
	virtual void OnPlayerStartTrial(APlayerController* Player);
	UFUNCTION(BlueprintCallable)
	virtual void OnPlayerFinishedTrial(APlayerController* Player, bool bIsPlayerDisqualified);
};
