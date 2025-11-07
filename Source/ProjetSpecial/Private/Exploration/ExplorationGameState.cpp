// Fill out your copyright notice in the Description page of Project Settings.


#include "Exploration/ExplorationGameState.h"

#include "Exploration/ExplorationGameMode.h"
#include "Networking/ProjetSpecialNetWorkSubsystem.h"

void AExplorationGameState::OnPlayerLoggedIn(APlayerController* newPlayer)
{
	if(!newPlayer->IsLocalController())
	{
		NbPlayers++;
	}
}

void AExplorationGameState::BeginPlay()
{
	Super::BeginPlay();
	if(auto GameMode = GetWorld()->GetAuthGameMode<AExplorationGameMode>())
	{
		TimerEndTime = GetWorld()->TimeSeconds + GameMode->GameTime;
		//OnRep_TimerEndTime();
		GetWorld()->GetSubsystem<UProjetSpecialNetWorkSubsystem>()->SetTimerEndTime(TimerEndTime);
		
	}
	if(HasAuthority())
	{
		UGameInstance* GameInstance = GetGameInstance();
		checkf(GameInstance,TEXT("There is no game instance"))
		
		const int NbLocal = GameInstance->GetLocalPlayers().Num();
		NbPlayers+=NbLocal;
	}
	
}

void AExplorationGameState::PlayerReady()
{
	NbPlayersReadyForTrial++;
	if(NbPlayersReadyForTrial >= NbPlayers)
	{
		GetWorld()->GetAuthGameMode<AExplorationGameMode>()->TravelToTrial();
	}
	OnPlayerReadyForTrialChangedDelegate.Broadcast(NbPlayersReadyForTrial);
}

void AExplorationGameState::PlayerNotReady()
{
	NbPlayersReadyForTrial--;
	OnPlayerReadyForTrialChangedDelegate.Broadcast(NbPlayersReadyForTrial);
}

int AExplorationGameState::GetNbPlayers()
{
	return NbPlayers;
}

