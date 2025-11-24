// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RaceGate.generated.h"

UCLASS()
class PROJETSPECIAL_API ARaceGate : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARaceGate();

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int GateNumber;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

};
