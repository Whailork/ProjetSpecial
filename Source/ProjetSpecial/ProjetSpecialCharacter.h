// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AutoCameraCharacter.h"
#include "FlyingMovementComponent.h"
#include "PowerUpComponent.h"
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
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	UPowerUpComponent* PowerUpComponent;
	
	UPROPERTY(BlueprintReadWrite)
	bool bIsRunning;
	UPROPERTY(BlueprintReadWrite)
	FRotator CachedRotation;
	UPROPERTY(BlueprintReadWrite)
	FRotator DeltaRotation;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MAX_WALK_SPEED = 400.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MAX_RUN_SPEED = 600.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MAX_STAMINA = 100;
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	float Stamina;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MAX_HEALTH = 100;
	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	float Health;
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	UFUNCTION()
	void PSCMove(const FInputActionValue& Value);
	virtual void DoJumpStart() override;

	virtual void DoMove(float Right, float Forward) override;
	UFUNCTION()
	void RunStart();
	UFUNCTION()
	void RunStop();
	UFUNCTION()
	void Running();
	UFUNCTION()
	void StaminaRegen();
	UFUNCTION()
	void PowerUpAdded(FPowerUpData newData,int LastQuantity);

	FTimerHandle StaminaSpendTimerHandle;
	FTimerHandle StaminaRegenHandle;

public:

	virtual void Tick(float DeltaSeconds) override;
	
};

