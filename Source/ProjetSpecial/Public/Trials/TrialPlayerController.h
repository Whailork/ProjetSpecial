// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjetSpecialPlayerController.h"
#include "GameFramework/PlayerController.h"
#include "TrialPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJETSPECIAL_API ATrialPlayerController : public AProjetSpecialPlayerController
{
	GENERATED_BODY()

protected:
	float TrialStartTime;
	float TrialEndTime;

	virtual void BeginPlay() override;
	UFUNCTION(BlueprintNativeEvent)
	void OnTrialFinished();
public:
	UFUNCTION(BlueprintCallable)
	void TrialStarted();
	UFUNCTION(BlueprintCallable)
	void TrialEnded();
	float GetTrialDuration() const;
	
};
