// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TrialPlayerController.h"
#include "RaceTrialPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJETSPECIAL_API ARaceTrialPlayerController : public ATrialPlayerController
{
	GENERATED_BODY()
	
public:
	ARaceTrialPlayerController();
	virtual float GetTrialDuration() const override;
	UPROPERTY(BlueprintReadOnly)
	int PreviousGate;
	UPROPERTY(BlueprintReadOnly)
	int GatesMissed;
	UPROPERTY(BlueprintReadOnly)
	float GateMissedPenalty;

	UFUNCTION(BlueprintCallable)
	void GateReached(int GateNb);
};
