// Fill out your copyright notice in the Description page of Project Settings.


#include "Lobby/LobbyGameState.h"

#include "ProjetSpecialGameInstance.h"
#include "Lobby/LobbyGamemode.h"

void ALobbyGameState::AddPlayer(AInputReceiver* askingActor)
{
	if(!CurrentPlayers.Contains(askingActor->GetController()))
	{
		if(CurrentPlayers.Num() < GetWorld()->GetAuthGameMode<ALobbyGamemode>()->MaxPlayerNb)
		{
			CurrentPlayers.Add(askingActor->GetController<APlayerController>());
			TotalPlayers++;
			OnPlayerAddedDelegate.Broadcast(askingActor->GetController<APlayerController>(),true);
		}
	}
}

void ALobbyGameState::PlayerReady()
{
	NbPlayersReady++;
	OnPlayersReadyChangedDelegate.Broadcast(NbPlayersReady);
	if(NbPlayersReady >=TotalPlayers)
	{
		GetGameInstance<UProjetSpecialGameInstance>()->SaveSkinDatas(true);
		GetWorld()->ServerTravel("/Game/Levels/Lvl_Island?listen");
	}
}

void ALobbyGameState::PlayerNotReady()
{
	NbPlayersReady--;
	OnPlayersReadyChangedDelegate.Broadcast(NbPlayersReady);
}
