// Fill out your copyright notice in the Description page of Project Settings.


#include "Exploration/ExplorationGameMode.h"

#include "ProjetSpecialGameInstance.h"
#include "Kismet/GameplayStatics.h"
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
	GetGameInstance<UProjetSpecialGameInstance>()->SavePowerUpDatas();
	OnSwitchToTrialDelegate.Broadcast(ChosenTrial);
	
}

void AExplorationGameMode::TravelToTrial()
{
	//travel to trial is now handled into the hud

	
	/*FTrialDataRow TrialData = *TrialsDataTable->FindRow<FTrialDataRow>(ChosenTrial,TEXT("Looking for chosenTrial data Row"));
	GEngine->AddOnScreenDebugMessage(-1,5,FColor::Black,TrialData.GameModeRef->GetPathName());
	GetWorld()->ServerTravel(*FPackageName::ObjectPathToPackageName(TrialLevelRef->GetPathName()).Append("?game=/Game/Blueprints/Trials/FlightRace/BP_FlightRaceTrialGameMode.BP_FlightRaceTrialGameMode_C"),true);
	FString Cmd = FPackageName::ObjectPathToPackageName(TrialLevelRef->GetPathName());
	
	Cmd += FString(TEXT("?game=/Game/Blueprints/Trials/FlightRace/BP_FlightRaceTrialGameMode.BP_FlightRaceTrialGameMode_C"));
	UGameplayStatics::OpenLevel(this,*FPackageName::ObjectPathToPackageName(TrialLevelRef->GetPathName()),true,FString(TEXT("?game=/Game/Blueprints/Trials/FlightRace/BP_FlightRaceTrialGameMode.BP_FlightRaceTrialGameMode_C")));
	*/
	//GEngine->SetClientTravel(GetWorld(), *Cmd, ETravelType::TRAVEL_Absolute );
}
