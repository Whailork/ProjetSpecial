// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputReceiver.h"
#include "GameFramework/GameStateBase.h"
#include "LobbyGameState.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPlayerAdded,APlayerController*,newPlayer,bool, IsLocal);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPlayersReadyChanged,int, NbPlayersReady);
UCLASS()
class PROJETSPECIAL_API ALobbyGameState : public AGameStateBase
{
	GENERATED_BODY()
private:
	UPROPERTY()
	TArray<APlayerController*> CurrentPlayers;

	UPROPERTY(BlueprintAssignable)
	FOnPlayerAdded OnPlayerAddedDelegate;
	UPROPERTY(BlueprintAssignable)
	FPlayersReadyChanged OnPlayersReadyChangedDelegate;

	
public:
	UPROPERTY(BlueprintReadOnly)
	int TotalPlayers;
	UPROPERTY(BlueprintReadOnly)
	int NbPlayersReady;
	UFUNCTION()
	void AddPlayer(AInputReceiver* askingActor);
	UFUNCTION(BlueprintCallable)
	void PlayerReady();
	UFUNCTION(BlueprintCallable)
	void PlayerNotReady();
	
};
