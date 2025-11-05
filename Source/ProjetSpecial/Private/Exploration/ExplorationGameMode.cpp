// Fill out your copyright notice in the Description page of Project Settings.


#include "Exploration/ExplorationGameMode.h"

void AExplorationGameMode::BeginPlay()
{
	Super::BeginPlay();
	if (UWorld* World = GetWorld())
	{
		if (UGameViewportClient* ViewportClient = World->GetGameViewport())
		{
			ViewportClient->SetForceDisableSplitscreen(false); 
		}
	}
}
