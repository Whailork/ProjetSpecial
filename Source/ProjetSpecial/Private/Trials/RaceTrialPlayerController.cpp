// Fill out your copyright notice in the Description page of Project Settings.


#include "Trials/RaceTrialPlayerController.h"

#include "Networking/ProjetSpecialNetWorkSubsystem.h"


ARaceTrialPlayerController::ARaceTrialPlayerController()
{
	PreviousGate = -1;
	GatesMissed = 0;
	GateMissedPenalty = 0;
}

float ARaceTrialPlayerController::GetTrialDuration() const
{
	if(!bIsTrialStarted)
	{
		return 0;
	}
	if(TrialEndTime != 0)
	{
		return TrialEndTime - TrialStartTime + GateMissedPenalty;
	}
	else
	{
		return GetWorld()->GetSubsystem<UProjetSpecialNetWorkSubsystem>()->GetCurrentServerTime() - TrialStartTime + GateMissedPenalty;
	}
}

void ARaceTrialPlayerController::GateReached(int GateNb)
{
	if(PreviousGate + 1 != GateNb && PreviousGate != GateNb)
	{
		GatesMissed++;
		GateMissedPenalty += GetTrialDuration()*0.1;
	}
	if(GateNb > PreviousGate)
	{
		PreviousGate = GateNb;
	}
	
}
