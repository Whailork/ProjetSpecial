// Fill out your copyright notice in the Description page of Project Settings.


#include "Trials/TrialPlayerController.h"

#include "Networking/ProjetSpecialNetWorkSubsystem.h"
#include "Trials/TrialGameStateBase.h"

void ATrialPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if(IsLocalController())
	{
		if(auto GameState = GetWorld()->GetGameState<ATrialGameStateBase>())
		{
			GameState->TrialFinishedDelegate.AddDynamic(this,&ATrialPlayerController::OnTrialFinished);
		}
		
	}
	
}

void ATrialPlayerController::OnTrialFinished_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1,5,FColor::Blue,FString("TrialFInished"));
	GEngine->AddOnScreenDebugMessage(-1,5,FColor::Blue,FString::SanitizeFloat(GetTrialDuration()));
}

void ATrialPlayerController::TrialStarted()
{
	if(!bIsTrialStarted)
	{
		TrialStartTime = GetWorld()->GetSubsystem<UProjetSpecialNetWorkSubsystem>()->GetCurrentServerTime();
		GetWorld()->GetGameState<ATrialGameStateBase>()->OnPlayerStartTrial(this);
		bIsTrialStarted = true;
	}
	
}

void ATrialPlayerController::TrialEnded(bool bIsPlayerDisqualified)
{
	if(!bIsTrialFinished)
	{
		TrialEndTime = GetWorld()->GetSubsystem<UProjetSpecialNetWorkSubsystem>()->GetCurrentServerTime();
		GetWorld()->GetGameState<ATrialGameStateBase>()->OnPlayerFinishedTrial(this,bIsPlayerDisqualified);
		bIsTrialFinished = true;
	}
	
}

float ATrialPlayerController::GetTrialDuration() const
{
	if(TrialEndTime != 0)
	{
		return TrialEndTime - TrialStartTime;
	}
	else
	{
		return GetWorld()->GetSubsystem<UProjetSpecialNetWorkSubsystem>()->GetCurrentServerTime() - TrialStartTime;
	}
	
}
