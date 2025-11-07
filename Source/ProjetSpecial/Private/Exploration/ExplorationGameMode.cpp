// Fill out your copyright notice in the Description page of Project Settings.


#include "Exploration/ExplorationGameMode.h"

#include "Networking/ProjetSpecialNetWorkSubsystem.h"
#include "Trials/TrialGameModeBase.h"


void AExplorationGameMode::BeginPlay()
{
	Super::BeginPlay();
	if (UWorld* World = GetWorld())
	{
		if (UGameViewportClient* ViewportClient = World->GetGameViewport())
		{
			ViewportClient->SetForceDisableSplitscreen(false); 
		}
		GetWorld()->GetSubsystem<UProjetSpecialNetWorkSubsystem>()->TimerEndReachedDelegate.AddDynamic(this,&AExplorationGameMode::OnGameTimeElapsed);
	}
	auto Names = TrialsDataTable->GetRowNames();
	int32 randomTrial = FMath::RandRange(0, Names.Num() -1);
	ChosenTrial = Names[randomTrial];
}

void AExplorationGameMode::OnGameTimeElapsed(float EndTime)
{
	GEngine->AddOnScreenDebugMessage(-1,1,FColor::Black,FString("travel to trial"));
	//do the random trial logic
	
	OnSwitchToTrialDelegate.Broadcast(ChosenTrial);
	
}

void AExplorationGameMode::TravelToTrial()
{
	FTrialDataRow TrialData = *TrialsDataTable->FindRow<FTrialDataRow>(ChosenTrial,TEXT("Looking for chosenTrial data Row"));
	GetWorld()->ServerTravel(*FPackageName::ObjectPathToPackageName(TrialData.LevelRef.ToString()) .Append("?listen"));
}
