// Fill out your copyright notice in the Description page of Project Settings.


#include "Exploration/ExplorationPlayerController.h"

#include "Exploration/ExplorationGameMode.h"

void AExplorationPlayerController::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetAuthGameMode<AExplorationGameMode>()->OnSwitchToTrialDelegate.AddDynamic(this, &AExplorationPlayerController::OnSwitchToTrial);
}

void AExplorationPlayerController::OnSwitchToTrial_Implementation(FName TrialName)
{
	SetPause(true);
}
