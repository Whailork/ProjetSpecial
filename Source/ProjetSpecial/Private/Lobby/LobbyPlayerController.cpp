// Fill out your copyright notice in the Description page of Project Settings.


#include "Lobby/LobbyPlayerController.h"

#include "Kismet/GameplayStatics.h"
#include "Lobby/LobbyGameState.h"

void ALobbyPlayerController::PlayerReady()
{
	GetWorld()->GetGameState<ALobbyGameState>()->PlayerReady();
}

void ALobbyPlayerController::PlayerNotReady()
{
	GetWorld()->GetGameState<ALobbyGameState>()->PlayerNotReady();
}
