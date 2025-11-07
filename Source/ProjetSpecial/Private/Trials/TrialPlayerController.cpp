// Fill out your copyright notice in the Description page of Project Settings.


#include "Trials/TrialPlayerController.h"

#include "Networking/ProjetSpecialNetWorkSubsystem.h"
#include "Trials/TrialGameStateBase.h"

void ATrialPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if(IsLocalController())
	{
		GetWorld()->GetGameState<ATrialGameStateBase>()->TrialFinishedDelegate.AddDynamic(this,&ATrialPlayerController::OnTrialFinished);
	}
	
}

void ATrialPlayerController::OnTrialFinished_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1,5,FColor::Blue,FString("TrialFInished"));
	GEngine->AddOnScreenDebugMessage(-1,5,FColor::Blue,FString::SanitizeFloat(GetTrialDuration()));
}

void ATrialPlayerController::TrialStarted()
{
	TrialStartTime = GetWorld()->GetSubsystem<UProjetSpecialNetWorkSubsystem>()->GetCurrentServerTime();
	GetWorld()->GetGameState<ATrialGameStateBase>()->OnPlayerStartTrial(this);
}

void ATrialPlayerController::TrialEnded()
{
	TrialEndTime = GetWorld()->GetSubsystem<UProjetSpecialNetWorkSubsystem>()->GetCurrentServerTime();
	GetWorld()->GetGameState<ATrialGameStateBase>()->OnPlayerFinishedTrial(this,false);
}

float ATrialPlayerController::GetTrialDuration() const
{
	return TrialEndTime - TrialStartTime;
}
