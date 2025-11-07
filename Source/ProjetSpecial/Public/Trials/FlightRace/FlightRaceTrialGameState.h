// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Trials/TrialGameStateBase.h"
#include "FlightRaceTrialGameState.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FFlightRaceData
{
	GENERATED_BODY()
	UPROPERTY()
	APlayerController* LinkedPlayer;
	float EndTime;
	float DistanceWithEnd;
	bool bHasFinishedRace;
	
};


UCLASS()
class PROJETSPECIAL_API AFlightRaceTrialGameState : public ATrialGameStateBase
{
	GENERATED_BODY()
	TArray<FFlightRaceData> RaceDatas;
	
	
	int NbPlayersFinished;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector FinalGatePosition;
	 TArray<FFlightRaceData> SortRaceDatas();
	
public:
	
	UFUNCTION()
	void OnPlayerFinishedRace(APawn* Player, bool bHasFinishedRace);
	virtual int32 GetFinishScore(APlayerController* Player) override;
	virtual void OnPlayerStartTrial(APlayerController* Player) override;
	virtual void OnPlayerFinishedTrial(APlayerController* Player, bool bIsPlayerDisqualified) override;
	
};
