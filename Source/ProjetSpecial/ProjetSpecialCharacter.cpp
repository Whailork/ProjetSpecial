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


	FlyingFriction = 10;
}

void AProjetSpecialCharacter::BeginPlay()
{
	Super::BeginPlay();
	CachedRotation = GetActorRotation();
	
}


void AProjetSpecialCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AProjetSpecialCharacter::DoJumpStart);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Canceled, this, &AProjetSpecialCharacter::DoJumpStart);
		
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AProjetSpecialCharacter::TakeOff);
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AProjetSpecialCharacter::PSCMove);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &AProjetSpecialCharacter::MoveStopped);
		EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Started,this,&AProjetSpecialCharacter::Run);


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

void AProjetSpecialCharacter::Run()
{
	
	if(GetCharacterMovement())
	{
		if(bIsRunning)
		{
			bIsRunning = false;
			TargetCameraLag = BASE_CAMERA_LAG_SPEED;
		}
		else
		{
			bIsRunning = true;
			TargetCameraLag = RUN_CAMERA_LAG_SPEED;		
		}
	}
	GetWorldTimerManager().SetTimer(CameraLagTransitionTimerHandle,this,&AProjetSpecialCharacter::AdjustCameraLag,0.1,true);
}

void AProjetSpecialCharacter::TakeOff()
{
	bIsTakingOff = true;
	if(auto PlayerController = Cast<APlayerController>(GetController()))
	{
		DisableInput(PlayerController);
	}
}

void AProjetSpecialCharacter::StartGliding()
{
	//AllowCameraAutoAdjust = false;
	//AllowCameraWallAvoidance = false;
	//AllowCameraPositionReset = false;
	AllowVerticalAutoAdjust = false;
	//AllowCliffDetection = false;
	bIsGliding = true;
	bIsTakingOff = false;
	GetCharacterMovement()->MaxWalkSpeed = BASE_FLYING_SPEED;
	currentFlyingSpeed = BASE_FLYING_SPEED;
	currentFlyingUpSpeed = BASE_FLYING_SPEED;
	GetCharacterMovement()->Velocity = GetActorForwardVector() * currentFlyingSpeed;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	//bUseControllerRotationPitch = true;
	//bUseControllerRotationYaw = true;
	//StopCameraPositionReset();
}


void AProjetSpecialCharacter::StopGliding()
{
	//AllowCameraAutoAdjust = true;
	//AllowCameraWallAvoidance = true;
	//AllowCameraPositionReset = true;
	AllowVerticalAutoAdjust = true;
	//AllowCliffDetection = true;
	bIsGliding = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	//bUseControllerRotationPitch = false;
	//bUseControllerRotationYaw = false;

	//GetWorldTimerManager().SetTimer(CameraPositionResetTimerHandle, this,&AAutoCameraCharacter::StartCameraPositionReset, CAMERA_POSITION_RESET_DELAY,false);
}

void AProjetSpecialCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(CanJump())
	{
		if(bIsGliding)
		{
			StopGliding();
		}
	}
	if(bIsGliding)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black,FString::SanitizeFloat(FlyingFriction));
		currentFlyingSpeed = currentFlyingSpeed - FlyingFriction*GetActorForwardVector().Z;
		currentFlyingUpSpeed = currentFlyingUpSpeed -1.5*FlyingFriction;
		FVector TempVelocity = GetActorForwardVector() * FMath::Max(currentFlyingSpeed,0);
		GetCharacterMovement()->Velocity = FVector(TempVelocity.X,TempVelocity.Y,TempVelocity.Z+(currentFlyingUpSpeed*DeltaSeconds));
	}
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
		if(bIsGliding)
		{
			StopGliding();
		}
		else
		{
			StartGliding();
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
	if(bIsGliding)
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
			if(!bIsGliding)
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


