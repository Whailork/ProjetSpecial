// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "FoodPickup.generated.h"


UENUM(BlueprintType)
enum EFoodType : uint8
{
	No UMETA(DisplayName = "No"),
	Fish UMETA(DisplayName = "Fish"),
	Steak UMETA(DisplayName = "Steak"),
	Drumstick UMETA(DisplayName = "Drumstick"),
	DragonFruit UMETA(DisplayName = "DragonFruit")

};


UCLASS()
class PROJETSPECIAL_API AFoodPickup : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFoodPickup();
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UWidgetComponent* AppearanceWidget;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UBoxComponent* BoxCollision;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UDataTable* PickupDataTable;

	EFoodType Type;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float HealPercentage;
	FTimerHandle SetCollisionTimerHandle;
	UFUNCTION()
	void SetCollisions();

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float DespawnDelay;
	FTimerHandle DespawnTimerHandle;
	UFUNCTION()
	void Despawn();
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	bool StartDespawnAnim;
	
	//void SetupValues(TEnumAsByte<EPowerUpType> typeValue, bool isNegativeValue);

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void SetupValues(EFoodType type);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
