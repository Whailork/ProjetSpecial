// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "GameFramework/Pawn.h"
#include "InputReceiver.generated.h"

UCLASS()
class PROJETSPECIAL_API AInputReceiver : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AInputReceiver();

	UPROPERTY(EditAnywhere)
	UInputAction* JoinAction;
	UPROPERTY(EditAnywhere)
	UInputAction* RotateAvatarAction;
	UPROPERTY(BlueprintReadWrite)
	AActor* LinkedAvatar;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void AddPlayer();
	UFUNCTION()
	void RotateAvatar(const FInputActionValue& Value);
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
