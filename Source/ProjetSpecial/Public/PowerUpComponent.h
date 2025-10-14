// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityPowerUp.h"
#include "FoodPickup.h"
#include "PowerUp.h"
#include "Components/ActorComponent.h"
#include "PowerUpComponent.generated.h"



USTRUCT(BlueprintType,Blueprintable)
struct FPowerUpData
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	int Quantity;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TEnumAsByte<EPowerUpType> Type;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TEnumAsByte<EAbilityPowerUpType> AbilityType = EAbilityPowerUpType::None;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TEnumAsByte<EFoodType> FoodType = EFoodType::No;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FPowerUpAddedDelegate,FPowerUpData,newPowerUpData,int,LastQuantity, EPowerUpType, type);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAbilityActivatedDelegate,EAbilityPowerUpType,AbilityType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FFoodPickedUpDelegate,EFoodType,FoodType,float, HealValue);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJETSPECIAL_API UPowerUpComponent : public UActorComponent
{
	GENERATED_BODY()

	
public:
	// Sets default values for this component's properties
	UPowerUpComponent();
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TArray<FPowerUpData> PowerUps;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TEnumAsByte<EAbilityPowerUpType> ActiveAbility;

	FPowerUpAddedDelegate PowerUpAddedDelegate;
	FAbilityActivatedDelegate AbilityActivatedDelegate;
	FFoodPickedUpDelegate FoodPickedUpDelegate;
	UFUNCTION(BlueprintCallable)
	void AddPowerUp(EPowerUpType type,bool isNegative);
	UFUNCTION(BlueprintCallable)
	void AddAbilityPowerUp(EAbilityPowerUpType AbilityType);
	UFUNCTION(BlueprintCallable)
	void AddFoodPickup(EFoodType type,float HealValue);
	UFUNCTION(BlueprintCallable)
	void DropPowerUps(int number);
		
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
