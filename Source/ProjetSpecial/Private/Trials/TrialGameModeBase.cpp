// Fill out your copyright notice in the Description page of Project Settings.


#include "Trials/TrialGameModeBase.h"

#include "Trials/TrialGameStateBase.h"
#include "Trials/TrialPlayerController.h"

void ATrialGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	GetGameState<ATrialGameStateBase>()->OnPlayerLoggedIn(NewPlayer);
}

AActor* ATrialGameModeBase::ChoosePlayerStart_Implementation(AController* Player)
{
	if(TrialSpawn.IsValid())
	{
		return TrialSpawn.Get();
	}
	return Super::ChoosePlayerStart_Implementation(Player);
}

ATrialGameModeBase::ATrialGameModeBase()
{
	PlayerControllerClass = ATrialPlayerController::StaticClass();
}
