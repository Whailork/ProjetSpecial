// Fill out your copyright notice in the Description page of Project Settings.


#include "FlyingMovementComponent.h"

#include "AutoCameraCharacter.h"
#include "PowerUpComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values for this component's properties
UFlyingMovementComponent::UFlyingMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	FlyingFrictionUp = 5;
	FlyingFrictionDown = 10;
	// ...
}


void UFlyingMovementComponent::TakeOff()
{
	bIsTakingOff = true;
	if(auto Pawn = Cast<APawn>(GetOwner()))
	{
		if(auto PlayerController = Cast<APlayerController>(Pawn->GetController()))
		{
			Pawn->DisableInput(PlayerController);
		}
	}
	
}

void UFlyingMovementComponent::StartGliding()
{
	if(auto autoCameraCharacter = Cast<AAutoCameraCharacter>(GetOwner()))
	{
		autoCameraCharacter->AllowVerticalAutoAdjust = false;
	}
	if(auto Character = Cast<ACharacter>(GetOwner()))
	{
		Character->GetCharacterMovement()->MaxWalkSpeed = BASE_FLYING_SPEED;
		Character->GetCharacterMovement()->Velocity = Character->GetActorForwardVector() * currentFlyingSpeed;
		Character->GetCharacterMovement()->bOrientRotationToMovement = false;
	}
	bIsGliding = true;
	bIsTakingOff = false;
	currentFlyingSpeed = BASE_FLYING_SPEED;
	currentFlyingUpSpeed = BASE_FLYING_SPEED;
	
}

void UFlyingMovementComponent::StopGliding()
{
	if(auto autoCameraCharacter = Cast<AAutoCameraCharacter>(GetOwner()))
	{
		autoCameraCharacter->AllowVerticalAutoAdjust = true;
	}
	if(auto Character = Cast<ACharacter>(GetOwner()))
	{
		Character->GetCharacterMovement()->bOrientRotationToMovement = true;
	}
	bIsGliding = false;
}

void UFlyingMovementComponent::CheckForGlide()
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

// Called when the game starts
void UFlyingMovementComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UFlyingMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(auto Character = Cast<ACharacter>(GetOwner()))
	{
		if(Character->CanJump())
		{
			if(bIsGliding)
			{
				StopGliding();
			}
		}
		if(bIsGliding)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black,FString::SanitizeFloat(FlyingFrictionUp));
			if(Character->GetActorForwardVector().Z < 0)
			{
				currentFlyingSpeed = FMath::Max(currentFlyingSpeed - FlyingFrictionDown*Character->GetActorForwardVector().Z - FlyingFrictionUp/2,125);;
			}
			else
			{
				currentFlyingSpeed = FMath::Max(currentFlyingSpeed - FlyingFrictionUp*Character->GetActorForwardVector().Z - FlyingFrictionUp/2,125);;
			}
		
			if(currentFlyingSpeed <= 150)
			{
				currentFlyingUpSpeed = currentFlyingUpSpeed -25*FlyingFrictionUp;
			}
			else
			{
				currentFlyingUpSpeed = currentFlyingUpSpeed -1.5*FlyingFrictionUp;
			}
		
			FVector TempVelocity = Character->GetActorForwardVector() * currentFlyingSpeed;
			Character->GetCharacterMovement()->Velocity = FVector(TempVelocity.X,TempVelocity.Y,TempVelocity.Z+(currentFlyingUpSpeed*DeltaTime));
		}
	}
	

	// ...
}

