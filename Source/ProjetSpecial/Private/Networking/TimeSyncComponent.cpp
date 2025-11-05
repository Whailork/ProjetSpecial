// Fill out your copyright notice in the Description page of Project Settings.


#include "Networking/TimeSyncComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Networking/ProjetSpecialNetWorkSubsystem.h"


// Sets default values for this component's properties
UTimeSyncComponent::UTimeSyncComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTimeSyncComponent::Server_Ping_Implementation(int Id, float clientTime)
{
	Client_Pong(Id,clientTime,UGameplayStatics::GetRealTimeSeconds(GetWorld()));
}


void UTimeSyncComponent::Client_Pong_Implementation(int Id, float clientTime, float serverTime)
{
	GetWorld()->GetSubsystem<UProjetSpecialNetWorkSubsystem>()->PacketReceived(Id,clientTime,serverTime);
}

// Called when the game starts
void UTimeSyncComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTimeSyncComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

