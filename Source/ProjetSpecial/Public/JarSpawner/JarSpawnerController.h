// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "JarSpawnerController.generated.h"

UCLASS()
class PROJETSPECIAL_API AJarSpawnerController : public AAIController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AJarSpawnerController();

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UBlackboardComponent* SpawnerBlackboard;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UBehaviorTreeComponent* SpawnerBehaviourTree;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
