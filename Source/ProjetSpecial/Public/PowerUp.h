// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Actor.h"
#include "PowerUp.generated.h"

UENUM(BlueprintType)
enum EPowerUpType : uint8
{
	Speed UMETA(DisplayName = "Speed"),
	Flight UMETA(DisplayName = "Flight"),
	AttackSpeed UMETA(DisplayName = "AttackSpeed"),
	Defense UMETA(DisplayName = "Defense"),
	Friction UMETA(DisplayName = "Friction"),
	Strength UMETA(DisplayName = "Strength"),
	Jump UMETA(DisplayName = "Jump"),
	Stamina UMETA(DisplayName = "Stamina"),
	Health UMETA(DisplayName = "Health"),
	All UMETA(DisplayName = "All"),
};

UCLASS()
class PROJETSPECIAL_API APowerUp : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APowerUp();
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UWidgetComponent* AppearanceWidget;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UBoxComponent* BoxCollision;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TEnumAsByte<EPowerUpType> Type;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	bool IsNegative;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
