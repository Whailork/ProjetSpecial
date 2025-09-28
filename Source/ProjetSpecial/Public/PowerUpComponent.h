// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PowerUp.h"
#include "Components/ActorComponent.h"
#include "PowerUpComponent.generated.h"



USTRUCT(BlueprintType)
struct FPowerUpData
{
	GENERATED_BODY()
	int Quantity;
	EPowerUpType Type;
	
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FPowerUpAddedDelegate,FPowerUpData,newPowerUpData,int,LastQuantity);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJETSPECIAL_API UPowerUpComponent : public UActorComponent
{
	GENERATED_BODY()

	
public:
	// Sets default values for this component's properties
	UPowerUpComponent();
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TArray<FPowerUpData> PowerUps;

	FPowerUpAddedDelegate PowerUpAddedDelegate;
	UFUNCTION(BlueprintCallable)
	void AddPowerUp(EPowerUpType type,bool isNegative);
		
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
