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

	

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
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
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AProjetSpecialCharacter::DoJumpStart);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AProjetSpecialCharacter::Move);
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


void AProjetSpecialCharacter::Run()
{
	
	if(GetCharacterMovement())
	{
		if(GetCharacterMovement()->MaxWalkSpeed == MAX_RUN_SPEED)
		{
			GetCharacterMovement()->MaxWalkSpeed = MAX_WALK_SPEED;
			TargetCameraLag = BASE_CAMERA_LAG_SPEED;
		}
		else
		{
			GetCharacterMovement()->MaxWalkSpeed = MAX_RUN_SPEED;
			TargetCameraLag = RUN_CAMERA_LAG_SPEED;
		}
	}
	GetWorldTimerManager().SetTimer(CameraLagTransitionTimerHandle,this,&AProjetSpecialCharacter::AdjustCameraLag,0.1,true);
}


void AProjetSpecialCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(CanJump())
	{
		if(bIsGliding)
		{
			bIsGliding = false;
		}
	}
	if(bIsGliding)
	{
		GetCharacterMovement()->Velocity = FVector(GetCharacterMovement()->Velocity.X,GetCharacterMovement()->Velocity.Y,-4000*DeltaSeconds);
	}
	DeltaRotation = GetActorRotation() - CachedRotation;
	DeltaRotation.Normalize();
	CachedRotation = GetActorRotation();
	
	
	
}


void AProjetSpecialCharacter::DoJumpStart()
{
	// signal the character to jump
	if(!CanJump())
	{
		if(bIsGliding)
		{
			//GetCharacterMovement()->SetMovementMode(MOVE_Falling);
			bIsGliding = false;
		}
		else
		{
			//GetCharacterMovement()->SetMovementMode(MOVE_Flying);
			bIsGliding = true;
		}
	}
	else
	{
		Jump();
	}

}


