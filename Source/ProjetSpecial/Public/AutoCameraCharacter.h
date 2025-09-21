// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "AutoCameraCharacter.generated.h"

UCLASS()
class PROJETSPECIAL_API AAutoCameraCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
protected:
	/** Jump Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	class UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* LookAction;

	/** Mouse Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MouseLookAction;

	/** Mouse Look Input Action */
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* RunAction;
public:
	// Sets default values for this character's properties
	AAutoCameraCharacter();

	//Auto Camera
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FRotator DesiredControlRotation;
	FVector PreviousLocation;
	double CameraAdjustStartThreshold;
	double CameraAdjustStopThreshold;
	double CameraAdjustSpeedMin;
	double CameraAdjustSpeedMax;
	double CameraAutoAdjustDisableDuration;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float YawAdjustmentSign;
	float CameraMovementInterpSpeed;
	bool AllowCameraAutoAdjust;
	bool AllowCameraWallAvoidance;
	bool AllowCameraPositionReset;
	bool AllowCliffDetection;
	bool AllowVerticalAutoAdjust;
	FTimerHandle CameraPositionResetTimerHandle;
	FTimerHandle CameraAutoAdjustTimerHandle;
	FTimerHandle CameraLagTransitionTimerHandle;
	float TargetCameraLag;
	float LastCameraMovementYawDirection;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CAMERA_POSITION_RESET_DELAY = 3;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float BASE_CAMERA_MOVEMENT_INTERP_SPEED = 4;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CAMERA_POSITION_RESET_INTERP_SPEED = 0.15;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float BASE_CAMERA_LAG_SPEED = 15;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float RUN_CAMERA_LAG_SPEED = 5;

	//Camera wall avoidance
	TArray<float> CollisionImpactYawDirections;
	float CollisionYawDirection;
	float WallAvoidanceSphereRadius;
	bool bMadeContact;
	bool bGetOutOfWallAdjust;
	UPROPERTY()
	TArray<AActor*> InsideWallActors;

	TArray<float> CollisionImpactPitchDirections;
	float CollisionPitchDirection;
	UFUNCTION()
	void StartCameraPositionReset();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called for movement input */
	void Move(const FInputActionValue& Value);
	UFUNCTION()
	void MoveStopped();
	
	/** Called for looking input */
	void Look(const FInputActionValue& Value);
	void LookStarted(const FInputActionValue& Value);
	void LookStopped(const FInputActionValue& Value);
	
	UFUNCTION()
	void AdjustCameraLag();
	UFUNCTION()
	void EnableCameraAutoAdjust();
	
	UFUNCTION()
	void StopCameraPositionReset();
	
	void ComputeAngularDifference();
	void ComputeCameraWallAvoidance();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Handles move inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Right, float Forward);

	/** Handles look inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoLook(float Yaw, float Pitch);

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpStart();

};
