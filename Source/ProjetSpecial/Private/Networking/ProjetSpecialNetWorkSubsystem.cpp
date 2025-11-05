// Fill out your copyright notice in the Description page of Project Settings.


#include "Networking/ProjetSpecialNetWorkSubsystem.h"

#include "Kismet/GameplayStatics.h"

UProjetSpecialNetWorkSubsystem::UProjetSpecialNetWorkSubsystem()
{
}

TStatId UProjetSpecialNetWorkSubsystem::GetStatId() const
{
	return GetStatID();
}

void UProjetSpecialNetWorkSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	Super::OnWorldBeginPlay(InWorld);
	FTimerHandle timerHandle;
	NbReceived = 0;
	TimerEndTime = -1;
	GetWorld()->GetTimerManager().SetTimer(timerHandle,this, &UProjetSpecialNetWorkSubsystem::SyncWithClients,1,true);
}

void UProjetSpecialNetWorkSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CurrentServerTime += DeltaTime;
	RemainingTimerTime = TimerEndTime - CurrentServerTime;

	if(RemainingTimerTime <= 0 && TimerEndTime != -1)
	{
		TimerEndReachedDelegate.Broadcast(TimerEndTime);
		TimerEndTime = -1;
	}
}

void UProjetSpecialNetWorkSubsystem::RegisterController(AProjetSpecialPlayerController* PlayerController)
{
	RegisteredControllers.Add(PlayerController);
}

void UProjetSpecialNetWorkSubsystem::PacketReceived(int Id, float Time, float ServerTime)
{
	//Compute ping time
	PingRTTs.Add(UGameplayStatics::GetRealTimeSeconds(GetWorld()) - Time);
	if(NbReceived > Id)
	{
		PingRTTs.Sort();
		//remove two shortest
		PingRTTs.RemoveAt(0);
		PingRTTs.RemoveAt(0);
		//remove to highest
		PingRTTs.RemoveAt(PingRTTs.Num()-1);
		PingRTTs.RemoveAt(PingRTTs.Num()-1);

		CurrentPingTime = 0;
		for (auto RTT : PingRTTs)
		{
			CurrentPingTime += RTT/2;
		}
		
		CurrentPingTime = CurrentPingTime/NbReceived;
		CurrentPacketLossPercentage = (14 - NbReceived)/14;
		NbReceived = 0;
		PingRTTs.Empty();

		CurrentServerTime = ServerTime + CurrentPingTime;
	}
	NbReceived++;	
}

void UProjetSpecialNetWorkSubsystem::SyncWithClients()
{
	for (auto PlayerController : RegisteredControllers)
	{
		for(int i = 0; i < 14; i++)
		{
			PlayerController->TimeSyncComponent->Server_Ping(i,UGameplayStatics::GetRealTimeSeconds(GetWorld()) );
		}
	}
}

float UProjetSpecialNetWorkSubsystem::GetRemainingTimerTime()
{
	RemainingTimerTime = TimerEndTime - CurrentServerTime;
	return RemainingTimerTime;
}

float UProjetSpecialNetWorkSubsystem::GetCurrentServerTime()
{
	return CurrentServerTime;
}

void UProjetSpecialNetWorkSubsystem::SetTimerEndTime(float newTime)
{
	TimerEndTime = newTime;
}
