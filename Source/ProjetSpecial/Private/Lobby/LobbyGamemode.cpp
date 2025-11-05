// Fill out your copyright notice in the Description page of Project Settings.


#include "Lobby/LobbyGamemode.h"

ALobbyGamemode::ALobbyGamemode()
{
	
}

void ALobbyGamemode::BeginPlay()
{
	Super::BeginPlay();
	if (UWorld* World = GetWorld())
	{
		if (UGameViewportClient* ViewportClient = World->GetGameViewport())
		{
			ViewportClient->SetForceDisableSplitscreen(true); 
		}
	}
	
}
