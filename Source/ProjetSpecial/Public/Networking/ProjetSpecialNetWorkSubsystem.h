// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjetSpecialPlayerController.h"
#include "Subsystems/WorldSubsystem.h"
#include "ProjetSpecialNetWorkSubsystem.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTimerEndReached,float,TimerEndTIme);
UCLASS()
class PROJETSPECIAL_API UProjetSpecialNetWorkSubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()
	UPROPERTY()
	TArray<AProjetSpecialPlayerController*> RegisteredControllers;
	
	
	virtual TStatId GetStatId() const override;
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	virtual void Tick(float DeltaTime) override;
	
	
	UFUNCTION()
	void SyncWithClients();
	int NbReceived;
	float CurrentPingTime;
	float CurrentPacketLossPercentage;
	TArray<double> PingRTTs;
	float CurrentServerTime;
	float TimerEndTime;
	float RemainingTimerTime;
public:
	UProjetSpecialNetWorkSubsystem();
	void PacketReceived(int Id, float Time, float ServerTime);
	void RegisterController(AProjetSpecialPlayerController* PlayerController);
	FTimerEndReached TimerEndReachedDelegate;
	UFUNCTION(BlueprintCallable)
	float GetRemainingTimerTime();
	UFUNCTION(BlueprintCallable)
	float GetCurrentServerTime();
	void SetTimerEndTime(float newTime);
};
