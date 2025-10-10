// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HitableActor.h"
#include "Components/BoxComponent.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "PowerUpCrate.generated.h"

UCLASS()
class PROJETSPECIAL_API APowerUpCrate : public AActor, public IHitableActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APowerUpCrate();
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//UBoxComponent* BoxComponent;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//class UGeometryCollectionComponent* Mesh;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnHittableObjectHit_Implementation(float damage, AActor* Source,FHitResult Hit) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
