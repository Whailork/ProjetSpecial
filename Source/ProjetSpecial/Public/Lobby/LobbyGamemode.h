// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LobbyGamemode.generated.h"

/**
 * 
 */
UCLASS()
class PROJETSPECIAL_API ALobbyGamemode : public AGameModeBase
{
	GENERATED_BODY()
	ALobbyGamemode();

	virtual void BeginPlay() override;
public:
	int MaxPlayerNb = 4;
};
