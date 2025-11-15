// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjetSpecialGameInstance.h"

TArray<FPowerUpData> UProjetSpecialGameInstance::GetPowerUpDatas(int LocalPlayerNumber)
{
	return SavedPowerUps[LocalPlayerNumber];
}

void UProjetSpecialGameInstance::AssignSavedPowerUps(TArray<APlayerController*> Players)
{
	for (int i = 0; i < Players.Num(); i++)
	{
		if(auto Pawn = Players[i]->GetPawn())
		{
			if(auto PowerUpComp = Pawn->GetComponentByClass<UPowerUpComponent>())
			{
				if(SavedPowerUps.Num() > i)
				{
					PowerUpComp->ImportPowerUpData(SavedPowerUps[i]);
				}
				
			}
		}
	}
}
