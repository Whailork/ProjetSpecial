// Fill out your copyright notice in the Description page of Project Settings.


#include "Lobby/InputReceiver.h"

#include "EnhancedInputComponent.h"
#include "ProjetSpecial.h"
#include "Kismet/GameplayStatics.h"
#include "Lobby/LobbyGamemode.h"
#include "Lobby/LobbyGameState.h"


// Sets default values
AInputReceiver::AInputReceiver()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AInputReceiver::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void AInputReceiver::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AInputReceiver::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		EnhancedInputComponent->BindAction(JoinAction, ETriggerEvent::Triggered, this,&AInputReceiver::AddPlayer );
	}
	else
	{
		UE_LOG(LogProjetSpecial, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}
void AInputReceiver::AddPlayer()
{
	if(auto GS = GetWorld()->GetGameState<ALobbyGameState>())
	{
		GS->AddPlayer(this);
	}
}



