// Fill out your copyright notice in the Description page of Project Settings.


#include "Exploration/ExplorationGameState.h"

#include "Exploration/ExplorationGameMode.h"
#include "Networking/ProjetSpecialNetWorkSubsystem.h"

void AExplorationGameState::BeginPlay()
{
	Super::BeginPlay();
	if(auto GameMode = GetWorld()->GetAuthGameMode<AExplorationGameMode>())
	{
		TimerEndTime = GetWorld()->TimeSeconds + GameMode->GameTime;
		//OnRep_TimerEndTime();
		GetWorld()->GetSubsystem<UProjetSpecialNetWorkSubsystem>()->SetTimerEndTime(TimerEndTime);
		GetWorld()->GetSubsystem<UProjetSpecialNetWorkSubsystem>()->TimerEndReachedDelegate.AddDynamic(this,&AExplorationGameState::OnGameTimeElapsed);
	}
	
}

void AExplorationGameState::OnGameTimeElapsed(float EndTime)
{
	GEngine->AddOnScreenDebugMessage(-1,1,FColor::Black,FString("travel to trial"));
	//GetWorld()->ServerTravel("/Game/Levels/Lvl_Lobby?listen");
}
