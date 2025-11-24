// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjetSpecialGameInstance.h"

#include "Lobby/InputReceiver.h"

void UProjetSpecialGameInstance::SavePowerUpDatas()
{
	SavedPowerUps.Empty();
	auto LocalPlayersArray = GetLocalPlayers();
	for (auto LocalPlayer : LocalPlayersArray)
	{
		UPowerUpComponent* PowerUpComp = LocalPlayer->PlayerController->GetPawn()->GetComponentByClass<UPowerUpComponent>();
		if(!PowerUpComp)
		{
			return;	
		}
		SavedPowerUps.Add(PowerUpComp->ExportPowerUpData());
	}
}

void UProjetSpecialGameInstance::ClearSavedPowerUpDatas()
{
	SavedPowerUps.Empty();
}

TArray<FPowerUpData> UProjetSpecialGameInstance::GetPowerUpDatas(int LocalPlayerNumber)
{
	
	if(SavedPowerUps.IsEmpty())
	{
		return TArray<FPowerUpData>();
	}
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

void UProjetSpecialGameInstance::SaveSkinDatas(bool FromLobby)
{
	SavedSkins.Empty();
	auto LocalPlayersArray = GetLocalPlayers();
	for (auto LocalPlayer : LocalPlayersArray)
	{
		if(FromLobby)
		{
			if(auto InputReceiver = Cast<AInputReceiver>(LocalPlayer->PlayerController->GetPawn()))
			{
				USkeletalMeshComponent* MeshComp = InputReceiver->LinkedAvatar->GetComponentByClass<USkeletalMeshComponent>();
				if(!MeshComp)
				{
					return;
				}
				FSKinData SkinData = FSKinData(MeshComp->GetSkeletalMeshAsset(),Cast<UMaterialInstance>(MeshComp->GetMaterial(0)),Cast<UMaterialInstance>(MeshComp->GetMaterial(1)));
				SavedSkins.Add(SkinData);
				
			}
		}
		else
		{
			USkeletalMeshComponent* MeshComp = LocalPlayer->PlayerController->GetPawn()->GetComponentByClass<USkeletalMeshComponent>();
			if(!MeshComp)
			{
				return;	
			}
			FSKinData SkinData = FSKinData(MeshComp->GetSkeletalMeshAsset(),Cast<UMaterialInstance>(MeshComp->GetMaterial(0)),Cast<UMaterialInstance>(MeshComp->GetMaterial(1)));
			SavedSkins.Add(SkinData);
		}
	}
}

void UProjetSpecialGameInstance::AssingSavedSkins(TArray<APlayerController*> Players)
{
	for (int i = 0; i < Players.Num(); i++)
	{
		if(auto Pawn = Players[i]->GetPawn())
		{
			if(auto SkeletalMesh = Pawn->GetComponentByClass<USkeletalMeshComponent>())
			{
				if(SavedSkins.Num() > i)
				{
					SkeletalMesh->SetSkeletalMesh(SavedSkins[i].SkeletalMesh);
					SkeletalMesh->SetMaterial(0,SavedSkins[i].SkinMaterial);
					SkeletalMesh->SetMaterial(1,SavedSkins[i].EyeMaterial);
				}
				
			}
		}
	}
}

FSKinData UProjetSpecialGameInstance::GetSkinData(int LocalPlayerNumber)
{

	FSKinData EmptyData = FSKinData();
	if(SavedSkins.IsEmpty())
	{
		return EmptyData;
	}
	return SavedSkins[LocalPlayerNumber];
}
