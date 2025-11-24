// Fill out your copyright notice in the Description page of Project Settings.


#include "Trials/RaceTrialGameState.h"

#include "Trials/RaceTrialPlayerController.h"

TArray<FRaceTrialData> ARaceTrialGameState::SortRaceDatas()
{
	TArray<FRaceTrialData> SortedArray;

	TArray<FRaceTrialData> FinishedPlayers;
	TArray<FRaceTrialData> DeadPlayers;

	
	
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
	FinishedPlayers.Sort([](const FRaceTrialData& A, const FRaceTrialData& B)
	{
		return A.EndTime > B.EndTime;
	});
	DeadPlayers.Sort([](const FRaceTrialData& A, const FRaceTrialData& B)
	{
		return A.DistanceWithEnd > B.DistanceWithEnd;
	});
	SortedArray.Append(FinishedPlayers);
	SortedArray.Append(DeadPlayers);
	return SortedArray;
}

void ARaceTrialGameState::OnPlayerFinishedRace(APawn* Player, bool bHasFinishedRace)
{
	ARaceTrialPlayerController* TrialPC = Cast<ARaceTrialPlayerController>(Player->GetController());
	checkf(TrialPC,TEXT("Trial game state put not a trial player controller"));
	FRaceTrialData newRaceData = FRaceTrialData(TrialPC,TrialPC->GetTrialDuration(),FVector::Dist(Player->GetActorLocation(),FinalGatePosition),bHasFinishedRace);

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

int32 ARaceTrialGameState::GetFinishScore(APlayerController* Player)
{
	TArray<FRaceTrialData> SortedDatas = SortRaceDatas();
	for (int i = 0; i < SortedDatas.Num(); i++)
	{
		if(SortedDatas[i].LinkedPlayer == Player)
		{
			return i+1;
		}
	}
	return Super::GetFinishScore(Player);
}

void ARaceTrialGameState::GetTrialTime(APlayerController* Player)
{
	
}

void ARaceTrialGameState::OnPlayerStartTrial(APlayerController* Player)
{
	Super::OnPlayerStartTrial(Player);
}

void ARaceTrialGameState::OnPlayerFinishedTrial(APlayerController* Player, bool bIsPlayerDisqualified)
{
	Super::OnPlayerFinishedTrial(Player, bIsPlayerDisqualified);
	OnPlayerFinishedRace(Player->GetPawnOrSpectator(),!bIsPlayerDisqualified);
}
