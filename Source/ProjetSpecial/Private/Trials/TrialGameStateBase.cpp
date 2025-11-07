// Fill out your copyright notice in the Description page of Project Settings.


#include "Trials/TrialGameStateBase.h"

#include "Kismet/GameplayStatics.h"
#include "Trials/TrialPlayerController.h"


void ATrialGameStateBase::BeginPlay()
{
	Super::BeginPlay();
	if(HasAuthority())
	{
		UGameInstance* GameInstance = GetGameInstance();
		checkf(GameInstance,TEXT("There is no game instance"))
		
		const int NbLocal = GameInstance->GetLocalPlayers().Num();
		NbPlayers+=NbLocal;
	}
	
}

void ATrialGameStateBase::OnPlayerLoggedIn(APlayerController* newPlayer)
{
	if(!newPlayer->IsLocalController())
	{
		NbPlayers++;
	}
	
}

int32 ATrialGameStateBase::GetFinishScore(APlayerController* Player)
{
	return -1;
}

void ATrialGameStateBase::OnPlayerStartTrial(APlayerController* Player)
{
	//ATrialPlayerController* TrialPC = Cast<ATrialPlayerController>(Player);
	//checkf(TrialPC,TEXT("Trial game state put not a trial player controller"));
	//TrialPC->TrialStarted();
	
}

void ATrialGameStateBase::OnPlayerFinishedTrial(APlayerController* Player,bool bIsPlayerDisqualified)
{
	//ATrialPlayerController* TrialPC = Cast<ATrialPlayerController>(Player);
	//checkf(TrialPC,TEXT("Trial game state put not a trial player controller"));
	//TrialPC->TrialEnded();
}
