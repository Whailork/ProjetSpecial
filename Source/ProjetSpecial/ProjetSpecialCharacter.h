// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AutoCameraCharacter.h"
#include "FlyingMovementComponent.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "ProjetSpecialCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

/**
 *  A simple player-controllable third person character
 *  Implements a controllable orbiting camera
 */
UCLASS(abstract)
class AProjetSpecialCharacter : public AAutoCameraCharacter
{
	GENERATED_BODY()

public:

	/** Constructor */
	AProjetSpecialCharacter();
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UFlyingMovementComponent* FlyingMovementComponent;
	
	//UPROPERTY(BlueprintReadWrite)
	//bool bIsGliding;
	UPROPERTY(BlueprintReadWrite)
	bool bIsRunning;
	//UPROPERTY(BlueprintReadWrite,EditAnywhere)
	//bool bIsTakingOff;
	UPROPERTY(BlueprintReadWrite)
	FRotator CachedRotation;
	UPROPERTY(BlueprintReadWrite)
	FRotator DeltaRotation;
	//float currentFlyingSpeed;
	//float currentFlyingUpSpeed;
	//UPROPERTY(BlueprintReadWrite,EditAnywhere)
	//float FlyingFriction;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MAX_WALK_SPEED = 400.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MAX_RUN_SPEED = 800.0f;
	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	//float GLIDING_GRAVITY_SCALE = 0.15f;
	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	//float REGULAR_GRAVITY_SCALE = 1.0f;
	//UPROPERTY(BlueprintReadWrite, EditAnywhere)
	//float BASE_FLYING_SPEED = 600.0f;
	//UPROPERTY(BlueprintReadWrite,EditAnywhere)
	//UInputAction* TakeOffAction;
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	UFUNCTION()
	void PSCMove(const FInputActionValue& Value);
	virtual void DoJumpStart() override;

	virtual void DoMove(float Right, float Forward) override;
	UFUNCTION(BlueprintCallable)
	void Run();
	//UFUNCTION(BlueprintCallable)
	//void TakeOff();

	//UFUNCTION(BlueprintCallable)
	//void StartGliding();
	//UFUNCTION(BlueprintCallable)
	//void StopGliding();
public:

	virtual void Tick(float DeltaSeconds) override;
	
};

