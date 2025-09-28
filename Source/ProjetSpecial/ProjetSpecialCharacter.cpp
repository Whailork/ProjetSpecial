// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjetSpecialCharacter.h"

#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "ProjetSpecial.h"

AProjetSpecialCharacter::AProjetSpecialCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	FlyingMovementComponent = CreateDefaultSubobject<UFlyingMovementComponent>("FlyingMovementComponent");
	PowerUpComponent = CreateDefaultSubobject<UPowerUpComponent>("PowerUpComponent");
	
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	
}

void AProjetSpecialCharacter::BeginPlay()
{
	Super::BeginPlay();
	CachedRotation = GetActorRotation();
	//we process upgrades
	
	for (auto PowerUp : PowerUpComponent->PowerUps)
	{
		switch (PowerUp.Type)
		{
			case EPowerUpType::Flight:
				FlyingMovementComponent->BASE_FLYING_SPEED += PowerUp.Quantity*18;
				break;
			case EPowerUpType::Friction:
				FlyingMovementComponent->FlyingFrictionDown += PowerUp.Quantity*0.2;
			FlyingMovementComponent->FlyingFrictionUp -= PowerUp.Quantity*0.2;
				break;
			case EPowerUpType::Speed:
				
				MAX_WALK_SPEED += PowerUp.Quantity*8;
				MAX_RUN_SPEED = MAX_WALK_SPEED +200;
				break;
			case EPowerUpType::Stamina:
				MAX_STAMINA += PowerUp.Quantity*10;
				break;
			case EPowerUpType::Jump:
				GetCharacterMovement()->JumpZVelocity += PowerUp.Quantity*10;
				break;
			case EPowerUpType::Strength:
				break;
			case EPowerUpType::AttackSpeed:
				break;
			case EPowerUpType::Health :
				MAX_HEALTH += PowerUp.Quantity*10;
				break;
			case EPowerUpType::Defense :
				break;
			case EPowerUpType::All :
				break;
			
		}
	}
	
	Stamina = MAX_STAMINA;
	Health = MAX_HEALTH;

	PowerUpComponent->PowerUpAddedDelegate.AddDynamic(this,&AProjetSpecialCharacter::PowerUpAdded);
	
}


void AProjetSpecialCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AProjetSpecialCharacter::DoJumpStart);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Canceled, this, &AProjetSpecialCharacter::DoJumpStart);
		
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, FlyingMovementComponent, &UFlyingMovementComponent::TakeOff);
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AProjetSpecialCharacter::PSCMove);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &AProjetSpecialCharacter::MoveStopped);

		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Started,this,&AProjetSpecialCharacter::RunStart);
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Completed,this,&AProjetSpecialCharacter::RunStop);
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Canceled,this,&AProjetSpecialCharacter::RunStop);


		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &AProjetSpecialCharacter::Look);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Started,this,&AProjetSpecialCharacter::LookStarted);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Completed,this,&AProjetSpecialCharacter::LookStopped);
		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AProjetSpecialCharacter::Look);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Started,this,&AProjetSpecialCharacter::LookStarted);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Completed,this,&AProjetSpecialCharacter::LookStopped);
	}
	else
	{
		UE_LOG(LogProjetSpecial, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AProjetSpecialCharacter::PSCMove(const FInputActionValue& Value)
{
	// input is a Vector2D
	if (CameraPositionResetTimerHandle.IsValid())
	{
		StopCameraPositionReset();
	}

	FVector2D MovementVector = Value.Get<FVector2D>();
	

	// route the input
	DoMove(MovementVector.X, MovementVector.Y);
}

void AProjetSpecialCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	DeltaRotation = GetActorRotation() - CachedRotation;
	DeltaRotation.Normalize();
	CachedRotation = GetActorRotation();
	if(DeltaRotation.Yaw > 2 || DeltaRotation.Yaw < -2)
	{
		DeltaRotation.Yaw = 0;
	}

}


void AProjetSpecialCharacter::DoJumpStart()
{
	// signal the character to jump
	if(!CanJump())
	{
		if(FlyingMovementComponent)
		{
			FlyingMovementComponent->CheckForGlide();
		}
		
	}
	else
	{
		Jump();
	}

}

void AProjetSpecialCharacter::DoMove(float Right, float Forward)
{
	float SpeedPercentage = FMath::Clamp(FMath::Abs(Right) + FMath::Abs(Forward),0,1);
	
	if(FlyingMovementComponent->bIsGliding)
	{
		SetActorRotation(FRotator(GetActorRotation().Pitch - Forward,GetActorRotation().Yaw + Right, GetActorRotation().Roll));
	}
	else
	{
		if(bIsRunning)
		{
			GetCharacterMovement()->MaxWalkSpeed = SpeedPercentage*MAX_RUN_SPEED;
			GetCharacterMovement()->MinAnalogWalkSpeed = SpeedPercentage*MAX_RUN_SPEED;
		}
		else
		{
			GetCharacterMovement()->MaxWalkSpeed = SpeedPercentage*MAX_WALK_SPEED;
			GetCharacterMovement()->MinAnalogWalkSpeed = SpeedPercentage*MAX_WALK_SPEED;
		}
		if (GetController() != nullptr)
		{
			// find out which way is forward
			const FRotator Rotation = GetController()->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get forward vector
			const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

			// get right vector 
			const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

			// add movement
			if(!FlyingMovementComponent->bIsGliding)
			{
				AddMovementInput(ForwardDirection, Forward);
				AddMovementInput(RightDirection, Right);
			}
			else
			{
				GetCharacterMovement()->Velocity = GetCharacterMovement()->Velocity + RightDirection*Right;
			}
		
		}
	}
}

void AProjetSpecialCharacter::RunStart()
{
	if(Stamina > 5)
	{
		bIsRunning = true;
		TargetCameraLag = RUN_CAMERA_LAG_SPEED;		
		GetWorldTimerManager().SetTimer(CameraLagTransitionTimerHandle,this,&AProjetSpecialCharacter::AdjustCameraLag,0.1,true);
		GetWorldTimerManager().SetTimer(StaminaSpendTimerHandle,this,&AProjetSpecialCharacter::Running,0.01,true);
		if(GetWorldTimerManager().IsTimerActive(StaminaRegenHandle))
		{
			GetWorldTimerManager().ClearTimer(StaminaRegenHandle);
		}
	}
	else
	{
		//too tired to run
	}
	
}

void AProjetSpecialCharacter::RunStop()
{
	if(bIsRunning)
	{
		bIsRunning = false;
		TargetCameraLag = BASE_CAMERA_LAG_SPEED;
		GetWorldTimerManager().SetTimer(CameraLagTransitionTimerHandle,this,&AProjetSpecialCharacter::AdjustCameraLag,0.1,true);
		if(GetWorldTimerManager().IsTimerActive(StaminaSpendTimerHandle))
		{
			GetWorldTimerManager().ClearTimer(StaminaSpendTimerHandle);
		}
	}
	if(!GetWorldTimerManager().IsTimerActive(StaminaRegenHandle))
	{
		GetWorldTimerManager().SetTimer(StaminaRegenHandle,this,&AProjetSpecialCharacter::StaminaRegen,0.01,true);
	}
	
}

void AProjetSpecialCharacter::Running()
{
	//GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green,FString("SpendStamina"));
	Stamina -=0.25;
	if(Stamina <= 0)
	{
		RunStop();
	}
}

void AProjetSpecialCharacter::StaminaRegen()
{
	Stamina+= 0.15;
	if(Stamina >= MAX_STAMINA)
	{
		if(GetWorldTimerManager().IsTimerActive(StaminaRegenHandle))
		{
			GetWorldTimerManager().ClearTimer(StaminaRegenHandle);
		}
	}
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green,FString("RegenStamina"));
}

void AProjetSpecialCharacter::PowerUpAdded(FPowerUpData newData,int LastQuantity)
{
	int QuantityDifference = newData.Quantity - LastQuantity;
	switch (newData.Type)
	{
		case EPowerUpType::Flight:
			FlyingMovementComponent->BASE_FLYING_SPEED += QuantityDifference*18;
			break;
		case EPowerUpType::Friction:
			FlyingMovementComponent->FlyingFrictionDown += QuantityDifference*0.7;
			if(FlyingMovementComponent->FlyingFrictionUp >= 0.5)
			{
				FlyingMovementComponent->FlyingFrictionUp -= QuantityDifference*0.05;
			}
			
			break;
		case EPowerUpType::Speed:
			MAX_WALK_SPEED += QuantityDifference*8;
			MAX_RUN_SPEED = MAX_WALK_SPEED +200;
			break;
		case EPowerUpType::Stamina:
			MAX_STAMINA += QuantityDifference*10;
			break;
		case EPowerUpType::Jump:
			GetCharacterMovement()->JumpZVelocity += QuantityDifference*10;
			break;
		case EPowerUpType::Strength:
			break;
		case EPowerUpType::AttackSpeed:
			break;
		case EPowerUpType::Health :
			MAX_HEALTH += QuantityDifference*10;
			break;
		case EPowerUpType::Defense :
			break;
		case EPowerUpType::All :
			break;
				
	}
}


