// Fill out your copyright notice in the Description page of Project Settings.


#include "JarSpawner/JarSpawnerController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "JarSpawner/JarSpawnerPawn.h"


// Sets default values
AJarSpawnerController::AJarSpawnerController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpawnerBlackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
	SpawnerBehaviourTree = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTree Component"));
}

// Called when the game starts or when spawned
void AJarSpawnerController::BeginPlay()
{
	Super::BeginPlay();
	
}

void AJarSpawnerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (auto SpawnerPawn = Cast<AJarSpawnerPawn>(InPawn))
	{
		// Check if the assets has been selected in the editor
		if (SpawnerPawn->BehaviorTreeAsset && SpawnerPawn->BehaviorTreeAsset->BlackboardAsset) {
			
			SpawnerBlackboard->InitializeBlackboard(*SpawnerPawn->BehaviorTreeAsset->BlackboardAsset);
			SpawnerBehaviourTree->StartTree(*SpawnerPawn->BehaviorTreeAsset);
		}
	}
}

// Called every frame
void AJarSpawnerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

