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


DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FPowerUpAddedDelegate,FPowerUpData,newPowerUpData,int,LastQuantity, EPowerUpType, type,bool,PowerUpDropped);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAbilityActivatedDelegate,EAbilityPowerUpType,AbilityType,bool, AbilityFinished);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FFoodPickedUpDelegate,EFoodType,FoodType,float, HealValue);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJETSPECIAL_API UPowerUpComponent : public UActorComponent
{
	GENERATED_BODY()

	
public:
	
	// Sets default values for this component's properties
	UPowerUpComponent();

	TArray<FPowerUpData> ExportPowerUpData();
	void ImportPowerUpData(TArray<FPowerUpData> PowerUpsInfo);
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TArray<FPowerUpData> PowerUps;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TEnumAsByte<EAbilityPowerUpType> ActiveAbility;

	bool bCanDropPowerUps;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,BlueprintAssignable)
	FPowerUpAddedDelegate PowerUpAddedDelegate;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,BlueprintAssignable)
	FAbilityActivatedDelegate AbilityActivatedDelegate;
	UPROPERTY(BlueprintReadWrite,EditAnywhere,BlueprintAssignable)
	FFoodPickedUpDelegate FoodPickedUpDelegate;
	UFUNCTION(BlueprintCallable)
	void AddPowerUp(EPowerUpType type,bool isNegative, bool PowerUpDropped = false, int NbAdded = 1);
	UFUNCTION(BlueprintCallable)
	void AddAbilityPowerUp(EAbilityPowerUpType AbilityType,bool AbilityFinished = false);
	UFUNCTION(BlueprintCallable)
	void AddFoodPickup(EFoodType type,float HealValue);
	UFUNCTION(BlueprintCallable)
	void DropPowerUps(int number);
	UFUNCTION(BlueprintCallable)
	FPowerUpData GetPowerUpsOfType(EPowerUpType type,bool& Success);
	
		
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
