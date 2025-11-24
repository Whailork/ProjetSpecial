// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TrialGameStateBase.h"
#include "RaceTrialGameState.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FRaceTrialData
{
	GENERATED_BODY()
	UPROPERTY()
	APlayerController* LinkedPlayer;
	float EndTime;
	float DistanceWithNextGate;
	int LastGate;
	bool bHasFinishedRace;
	
};

UCLASS()
class PROJETSPECIAL_API ARaceTrialGameState : public ATrialGameStateBase
{
	GENERATED_BODY()

	TArray<FRaceTrialData> RaceDatas;
	
	
	int NbPlayersFinished;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector FinalGatePosition;
	TArray<FRaceTrialData> SortRaceDatas();
	
public:
	UFUNCTION(BlueprintCallable)
	void OnPlayerFinishedRace(APawn* Player, bool bHasFinishedRace);
	virtual int32 GetFinishScore(APlayerController* Player) override;
	void GetTrialTime(APlayerController* Player);
	virtual void OnPlayerStartTrial(APlayerController* Player) override;
	virtual void OnPlayerFinishedTrial(APlayerController* Player, bool bIsPlayerDisqualified) override;
};
