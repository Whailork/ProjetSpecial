// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Niagara/Public/NiagaraComponent.h"
#include "HitableActor.h"
#include "ProjetSpecialCharacter.h"
#include "Fireball.generated.h"


UCLASS()
class PROJETSPECIAL_API AFireball : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFireball();
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	USphereComponent* SphereComponent;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UNiagaraComponent* Particles;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UProjectileMovementComponent* ProjectileMovementComponent;
	UPROPERTY(BlueprintReadWrite,EditAnywhere);
	AProjetSpecialCharacter* SpawnerCharacter;
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
