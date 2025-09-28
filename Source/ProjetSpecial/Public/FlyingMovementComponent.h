// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "Components/ActorComponent.h"
#include "FlyingMovementComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJETSPECIAL_API UFlyingMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFlyingMovementComponent();
	UPROPERTY(BlueprintReadWrite)
	bool bIsGliding;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	bool bIsTakingOff;
	
	float currentFlyingSpeed;
	float currentFlyingUpSpeed;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float FlyingFriction;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float BASE_FLYING_SPEED = 600.0f;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UInputAction* TakeOffAction;

	UFUNCTION(BlueprintCallable)
	void TakeOff();

	UFUNCTION(BlueprintCallable)
	void StartGliding();
	UFUNCTION(BlueprintCallable)
	void StopGliding();

	UFUNCTION(BlueprintCallable)
	void CheckForGlide();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
