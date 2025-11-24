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
	bool bIsTrialStarted;
	bool bIsTrialFinished;
	UPROPERTY(BlueprintReadOnly)
	float TrialStartTime = 0;
	UPROPERTY(BlueprintReadOnly)
	float TrialEndTime = 0;

	virtual void BeginPlay() override;
	UFUNCTION(BlueprintNativeEvent)
	void OnTrialFinished();
public:
	UFUNCTION(BlueprintCallable)
	void TrialStarted();
	UFUNCTION(BlueprintCallable)
	void TrialEnded(bool bIsPlayerDisqualified = false);
	UFUNCTION(BlueprintCallable)
	virtual float GetTrialDuration() const;
	
};
