// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TrialGameModeBase.generated.h"

/**
 * 
 */

class ATrialGameModeBase;

USTRUCT(BlueprintType)
struct FTrialDataRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TrialData")
	TSubclassOf<ATrialGameModeBase> GameModeRef;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TrialData")
	UTexture2D* TrialBackground;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TrialData")
	FString Description;
	
};

UCLASS()
class PROJETSPECIAL_API ATrialGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	virtual void PostLogin(APlayerController* NewPlayer) override;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<AActor> TrialSpawn;

	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
public:
	ATrialGameModeBase();
	
};
