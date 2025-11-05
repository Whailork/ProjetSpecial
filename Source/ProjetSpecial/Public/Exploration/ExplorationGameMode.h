// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ExplorationGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJETSPECIAL_API AExplorationGameMode : public AGameModeBase
{
	GENERATED_BODY()
	virtual void BeginPlay() override;

public:
	//game time is in seconds
	UPROPERTY(BlueprintReadOnly)
	float GameTime = 10;
};
