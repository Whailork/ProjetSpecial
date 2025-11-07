// Fill out your copyright notice in the Description page of Project Settings.


#include "Trials/FlightRace/FlightRaceTrialGameState.h"

#include "Trials/TrialPlayerController.h"

TArray<FFlightRaceData> AFlightRaceTrialGameState::SortRaceDatas()
{
	TArray<FFlightRaceData> SortedArray;

	TArray<FFlightRaceData> FinishedPlayers;
	TArray<FFlightRaceData> DeadPlayers;

	
	
	for (auto Data : RaceDatas)
	{
		if(Data.bHasFinishedRace)
		{
			FinishedPlayers.Add(Data);
		}
		else
		{
			DeadPlayers.Add(Data);
		}
	}
	FinishedPlayers.Sort([](const FFlightRaceData& A, const FFlightRaceData& B)
	{
		return A.EndTime > B.EndTime;
	});
	DeadPlayers.Sort([](const FFlightRaceData& A, const FFlightRaceData& B)
	{
		return A.DistanceWithEnd > B.DistanceWithEnd;
	});
	SortedArray.Append(FinishedPlayers);
	SortedArray.Append(DeadPlayers);
	return SortedArray;
	
}

void AFlightRaceTrialGameState::OnPlayerFinishedRace(APawn* Player, bool bHasFinishedRace)
{
	ATrialPlayerController* TrialPC = Cast<ATrialPlayerController>(Player->GetController());
	checkf(TrialPC,TEXT("Trial game state put not a trial player controller"));
	FFlightRaceData newRaceData = FFlightRaceData(TrialPC,TrialPC->GetTrialDuration(),FVector::Dist(Player->GetActorLocation(),FinalGatePosition),bHasFinishedRace);

	for (auto Data : RaceDatas)
	{
		if(Data.LinkedPlayer == Cast<APlayerController>(Player->GetController()))
		{
			return;
		}
	}
	RaceDatas.Add(newRaceData);
	NbPlayersFinished++;
	if(NbPlayersFinished >= NbPlayers)
	{
		TrialFinishedDelegate.Broadcast();
	}
}

int32 AFlightRaceTrialGameState::GetFinishScore(APlayerController* Player)
{
	TArray<FFlightRaceData> SortedDatas = SortRaceDatas();
	for (int i = 0; i < SortedDatas.Num(); i++)
	{
		if(SortedDatas[i].LinkedPlayer == Player)
		{
			return i+1;
		}
	}
	return Super::GetFinishScore(Player);
}

void AFlightRaceTrialGameState::OnPlayerStartTrial(APlayerController* Player)
{
	Super::OnPlayerStartTrial(Player);
}

void AFlightRaceTrialGameState::OnPlayerFinishedTrial(APlayerController* Player, bool bIsPlayerDisqualified)
{
	Super::OnPlayerFinishedTrial(Player, bIsPlayerDisqualified);
	OnPlayerFinishedRace(Player->GetPawnOrSpectator(),bIsPlayerDisqualified);
}


