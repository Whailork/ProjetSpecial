// Fill out your copyright notice in the Description page of Project Settings.


#include "AutoCameraCharacter.h"

#include "EnhancedInputComponent.h"
#include "ProjetSpecial.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
AAutoCameraCharacter::AAutoCameraCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->CameraLagSpeed = 15;
	CameraBoom->bEnableCameraLag = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;


	//for camera auto adjust
	CameraAdjustStartThreshold = 60;
	CameraAdjustStopThreshold = 140;
	CameraAdjustSpeedMin = 1;
	CameraAdjustSpeedMax = 1;
	CameraAutoAdjustDisableDuration = 2;
	YawAdjustmentSign = 0;
	CameraMovementInterpSpeed = BASE_CAMERA_MOVEMENT_INTERP_SPEED;
	AllowCameraAutoAdjust = true;
	AllowCameraWallAvoidance = true;
	AllowCameraPositionReset = true;
	AllowCliffDetection = true;
	AllowVerticalAutoAdjust = true;

	//for camera wall avoidance
	WallAvoidanceSphereRadius = 100;
}

// Called when the game starts or when spawned
void AAutoCameraCharacter::BeginPlay()
{
	Super::BeginPlay();
	DesiredControlRotation = GetControlRotation();
	PreviousLocation = GetActorLocation();
}

void AAutoCameraCharacter::Move(const FInputActionValue& Value)
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

void AAutoCameraCharacter::MoveStopped()
{
	if (CameraPositionResetTimerHandle.IsValid())
	{
		StopCameraPositionReset();
	}
	if(AllowCameraPositionReset)
	{
		GetWorldTimerManager().SetTimer(CameraPositionResetTimerHandle, this,&AAutoCameraCharacter::StartCameraPositionReset, CAMERA_POSITION_RESET_DELAY ,false);
	}
	
}

void AAutoCameraCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// route the input
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void AAutoCameraCharacter::LookStarted(const FInputActionValue& Value)
{
	StopCameraPositionReset();
	AllowCameraAutoAdjust = false;
	AllowCameraWallAvoidance = false;
	if (CameraAutoAdjustTimerHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(CameraAutoAdjustTimerHandle);
	}
	
	GetWorldTimerManager().SetTimer(CameraAutoAdjustTimerHandle, this, &AAutoCameraCharacter::EnableCameraAutoAdjust,
									CameraAutoAdjustDisableDuration, false);
	
	
}

void AAutoCameraCharacter::LookStopped(const FInputActionValue& Value)
{
	if (CameraPositionResetTimerHandle.IsValid())
	{
		StopCameraPositionReset();
	}
	if(AllowCameraPositionReset)
	{
		GetWorldTimerManager().SetTimer(CameraPositionResetTimerHandle, this,
									&AAutoCameraCharacter::StartCameraPositionReset, CAMERA_POSITION_RESET_DELAY,
									false);
	}
	
}

void AAutoCameraCharacter::AdjustCameraLag()
{
	CameraBoom->CameraLagSpeed = FMath::FInterpTo(CameraBoom->CameraLagSpeed, TargetCameraLag, 0.1, 2);
	if (FMath::IsNearlyEqual(CameraBoom->CameraLagSpeed, TargetCameraLag, 0.5))
	{
		GetWorldTimerManager().ClearTimer(CameraLagTransitionTimerHandle);
	}
}

void AAutoCameraCharacter::EnableCameraAutoAdjust()
{
	AllowCameraAutoAdjust = true;
	AllowCameraWallAvoidance = true;
	AllowCameraPositionReset = true;
}

void AAutoCameraCharacter::StartCameraPositionReset()
{
	AllowCameraWallAvoidance = false;
	FRotator DefaultRotation = GetActorRotation();
	if(AllowCliffDetection)
	{
		FHitResult outHit;
		TArray<AActor*> ActorsToIgnore;
		ActorsToIgnore.Add(this);
		FCollisionQueryParams Params;
		Params.AddIgnoredActors(ActorsToIgnore);
		FVector TraceStart = GetActorLocation() + GetActorForwardVector() * 100 + GetActorUpVector() * -100;
		FVector TraceEnd = TraceStart + FVector(0, 0, -0.001);


		bool HasHit = GetWorld()->SweepSingleByChannel(outHit, TraceStart, TraceEnd, FQuat::Identity,
													   UEngineTypes::ConvertToCollisionChannel(TraceTypeQuery1),
													   FCollisionShape::MakeSphere(50), Params);
		//bool HasHit = UKismetSystemLibrary::SphereTraceSingle(GetWorld(),TraceStart,TraceEnd,50,TraceTypeQuery1,false,ActorsToIgnore,EDrawDebugTrace::ForDuration,outHit,true);
		if (!HasHit)
		{
			DefaultRotation.Pitch -= 45;
		}
		else
		{
			if (outHit.ImpactNormal.Z > 0)
			{
				DefaultRotation.Pitch += FVector::DotProduct(GetActorForwardVector(), outHit.ImpactNormal) * -45;
			}
		}
	}
	
	CameraMovementInterpSpeed = CAMERA_POSITION_RESET_INTERP_SPEED;
	DesiredControlRotation = DefaultRotation;
}

void AAutoCameraCharacter::StopCameraPositionReset()
{
	AllowCameraWallAvoidance = true;
	CameraMovementInterpSpeed = BASE_CAMERA_MOVEMENT_INTERP_SPEED;
	DesiredControlRotation = GetControlRotation();
	GetWorldTimerManager().ClearTimer(CameraPositionResetTimerHandle);
}

void AAutoCameraCharacter::ComputeAngularDifference()
{
	if (AllowCameraAutoAdjust)
	{
		if (GetLastMovementInputVector().Length() > 0 || GetCharacterMovement()->IsFalling())
		{
			FRotator difference = GetBaseAimRotation() - RootComponent->GetComponentRotation();
			difference.Normalize();

			if (FMath::Abs(difference.Yaw) >= CameraAdjustStartThreshold && FMath::Abs(difference.Yaw) <= CameraAdjustStopThreshold)
			{
				double MappedAdjustValue = FMath::GetMappedRangeValueClamped(
					TRange<double>(CameraAdjustStartThreshold, CameraAdjustStopThreshold),
					TRange<double>(CameraAdjustSpeedMin, CameraAdjustSpeedMax), FMath::Abs(difference.Yaw));
				if (difference.Yaw > 0)
				{
					YawAdjustmentSign = -1;
				}
				else
				{
					YawAdjustmentSign = 1;
				}
				DesiredControlRotation.Yaw = DesiredControlRotation.Yaw + (MappedAdjustValue * YawAdjustmentSign);
				//AddControllerYawInput(MappedAdjustValue*YawAdjustmentSign);
			}
			else
			{
				YawAdjustmentSign = 0;
			}
			FVector DiffLocation = GetActorLocation() - PreviousLocation;
			DiffLocation.Normalize();

			PreviousLocation = GetActorLocation();


			//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black FString::SanitizeFloat(DiffLocation.Rotation().Pitch));
			if(AllowVerticalAutoAdjust)
			{
				if (!FMath::IsNearlyEqual(DiffLocation.Rotation().Pitch, 0, 0.1))
				{
					if (DiffLocation.Rotation().Pitch < 0)
					{
						DesiredControlRotation.Pitch = FMath::Max(DesiredControlRotation.Pitch - 1,
																  DiffLocation.Rotation().Pitch + 10);
					}
					else
					{
						DesiredControlRotation.Pitch = FMath::Min(DesiredControlRotation.Pitch + 1,
																  DiffLocation.Rotation().Pitch - 10);
					}
				}
			}
			

			//AddControllerYawInput(MappedAdjustValue*YawAdjustmentSign);
		}
	}
}

void AAutoCameraCharacter::ComputeCameraWallAvoidance()
{
	if (AllowCameraWallAvoidance)
	{
		TArray<FHitResult> ProximityHitResults;

		FCollisionObjectQueryParams ObjectParams;
		ObjectParams.AddObjectTypesToQuery(ECC_WorldStatic);
		ObjectParams.AddObjectTypesToQuery(ECC_WorldDynamic);

		TArray<AActor*> ActorsToIgnore;
		ActorsToIgnore.Add(this);
		FCollisionQueryParams Params;
		Params.AddIgnoredActors(ActorsToIgnore);
		//TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypesArray;
		//ObjectTypesArray.Add(UEngineTypes::ConvertToObjectType(ECC_WorldStatic));
		//ObjectTypesArray.Add(UEngineTypes::ConvertToObjectType(ECC_WorldDynamic));

		bMadeContact = GetWorld()->SweepMultiByObjectType(ProximityHitResults, FollowCamera->GetComponentLocation(),
		                                                  (GetActorLocation() + FVector(0, 0, 40)) - (FollowCamera->
			                                                  GetForwardVector() * 100), FQuat::Identity, ObjectParams,
		                                                  FCollisionShape::MakeSphere(WallAvoidanceSphereRadius),
		                                                  Params);
		//bMadeContact = UKismetSystemLibrary::SphereTraceMultiForObjects(this, FollowCamera->GetComponentLocation(), (GetActorLocation() + FVector(0,0,40)) - (FollowCamera->GetForwardVector() * 100), WallAvoidanceSphereRadius,ObjectTypesArray, false, TArray<AActor*>(),EDrawDebugTrace::None , ProximityHitResults, true);
		if (bMadeContact)
		{
			for (auto ProximityHitResult : ProximityHitResults)
			{
				if (bGetOutOfWallAdjust)
				{
					if (InsideWallActors.Contains(ProximityHitResult.GetActor()))
					{
						CollisionImpactYawDirections.Add(1 * LastCameraMovementYawDirection);
						GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green,
						                                 FString::SanitizeFloat(LastCameraMovementYawDirection));
					}
					else
					{
						bGetOutOfWallAdjust = false;
						InsideWallActors.Empty();
					}
				}
				else
				{
					bool ImpactNormalPointsUp = ProximityHitResult.ImpactNormal.Z > 0.5;
					FVector X, Y, Z;
					//get axes
					FRotationMatrix R(GetControlRotation());
					R.GetScaledAxes(X, Y, Z);

					FVector ControlForwardVector = FVector(X.X, X.Y, 0);
					FVector ImpactNormalVector = FVector(ProximityHitResult.ImpactNormal.X,
					                                     ProximityHitResult.ImpactNormal.Y, 0);

					FRotator ImpactRot = FRotator(0, ImpactNormalVector.Rotation().Yaw, 0);
					FRotator ControlRot = FRotator(0, ControlForwardVector.Rotation().Yaw, 0);


					if (!FMath::IsNearlyEqual(FMath::Abs(FVector::DotProduct(ControlForwardVector, ImpactNormalVector)),
					                          1,
					                          0.1))
					{
						if (!ImpactNormalVector.IsNearlyZero(0.01))
						{
							FRotator DeltaRotator = GetControlRotation() - ImpactNormalVector.Rotation();
							DeltaRotator.Normalize();
							float distance = ProximityHitResult.ImpactPoint.Distance(
								ProximityHitResult.ImpactPoint, ProximityHitResult.TraceStart);
							float MappedDistance = FMath::GetMappedRangeValueClamped(
								TRange<float>(0, WallAvoidanceSphereRadius), TRange<float>(1, 0.1), distance);
							if (!ImpactNormalPointsUp)
							{
								CollisionImpactYawDirections.Add(MappedDistance * FMath::Sign(DeltaRotator.Yaw) * 5);
							}
							else
							{
								if (!ImpactRot.EqualsOrientation(ControlRot, 1.2) && !ImpactRot.EqualsOrientation(
									ControlRot.Add(0, 180, 0), 1.2))
								{
									CollisionImpactYawDirections.
										Add(MappedDistance * FMath::Sign(DeltaRotator.Yaw) * 5);
								}
							}
						}
					}
					else
					{
						GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Blue, FString("InsideWall"));
						bGetOutOfWallAdjust = true;
						if (!InsideWallActors.Contains(ProximityHitResult.GetActor()))
						{
							InsideWallActors.Add(ProximityHitResult.GetActor());
						}
						FVector Dist = GetActorLocation() - ProximityHitResult.ImpactPoint;
						Dist.Normalize();

						LastCameraMovementYawDirection = FMath::Sign(Dist.Rotation().Yaw);

						if (LastCameraMovementYawDirection == 0)
						{
							FRotator DeltaControlRot = GetControlRotation() - DesiredControlRotation;
							DeltaControlRot.Normalize();

							LastCameraMovementYawDirection = -1 * FMath::Sign(DeltaControlRot.Yaw);
						}
						GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green,
						                                 FString::SanitizeFloat(LastCameraMovementYawDirection));
						CollisionImpactYawDirections.Add(1 * LastCameraMovementYawDirection);
					}
				}
			}
			if (!CollisionImpactYawDirections.IsEmpty())
			{
				for (auto YawDirection : CollisionImpactYawDirections)
				{
					CollisionYawDirection += YawDirection;
				}
				if (CollisionImpactPitchDirections.Num() > 1)
				{
					if (!FMath::IsNearlyEqual(CollisionYawDirection, 0, 2))
					{
						DesiredControlRotation = FRotator(DesiredControlRotation.Pitch,
						                                  DesiredControlRotation.Yaw + CollisionYawDirection,
						                                  DesiredControlRotation.Roll);
					}
				}
				else
				{
					if (!FMath::IsNearlyEqual(CollisionYawDirection, 0, 0.1))
					{
						DesiredControlRotation = FRotator(DesiredControlRotation.Pitch,
						                                  DesiredControlRotation.Yaw + CollisionYawDirection,
						                                  DesiredControlRotation.Roll);
					}
				}
			}
			CollisionImpactYawDirections.Empty();
			CollisionYawDirection = 0;
		}
		else
		{
			bGetOutOfWallAdjust = false;
			InsideWallActors.Empty();
		}
	}
}

// Called every frame
void AAutoCameraCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ComputeAngularDifference();
	ComputeCameraWallAvoidance();
	
	FRotator intepRotator = FMath::RInterpTo(GetControlRotation(),DesiredControlRotation,DeltaTime,CameraMovementInterpSpeed);
	
	
	if(!GetControlRotation().Equals(DesiredControlRotation,0.00001))
	{
		
		if(GetController())
		{
			
			APlayerController* PlayerController = Cast<APlayerController>(GetController());
			PlayerController->SetControlRotation(intepRotator);
		}
	}
}

// Called to bind functionality to input
void AAutoCameraCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AAutoCameraCharacter::DoJumpStart);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAutoCameraCharacter::Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &AAutoCameraCharacter::MoveStopped);


		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &AAutoCameraCharacter::Look);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Started,this,&AAutoCameraCharacter::LookStarted);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Completed,this,&AAutoCameraCharacter::LookStopped);
		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AAutoCameraCharacter::Look);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Started,this,&AAutoCameraCharacter::LookStarted);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Completed,this,&AAutoCameraCharacter::LookStopped);
	}
	else
	{
		UE_LOG(LogProjetSpecial, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AAutoCameraCharacter::DoMove(float Right, float Forward)
{
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
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void AAutoCameraCharacter::DoLook(float Yaw, float Pitch)
{
	DesiredControlRotation = FRotator(DesiredControlRotation.Pitch - Pitch,DesiredControlRotation.Yaw + Yaw, DesiredControlRotation.Roll);
}

void AAutoCameraCharacter::DoJumpStart()
{
	// signal the character to jump
	if(CanJump())
	{
		Jump();
	}
	
}
