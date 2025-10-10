// Fill out your copyright notice in the Description page of Project Settings.


#include "Fireball.h"

#include "HitableActor.h"



// Sets default values
AFireball::AFireball()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	RootComponent = SphereComponent;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	StaticMeshComponent->SetupAttachment(SphereComponent);

	Particles = CreateDefaultSubobject<UNiagaraComponent>("Particles");
	Particles->SetupAttachment(SphereComponent);
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
}

void AFireball::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor != SpawnerCharacter)
	{
		if(OtherActor->Implements<UHitableActor>())
		{
			if(auto HitableActor = Cast<IHitableActor>(OtherActor))
			{
				HitableActor->Execute_OnHittableObjectHit(OtherActor,SpawnerCharacter->Strength,this,SweepResult);
			}
		}
	}
	
}

// Called when the game starts or when spawned
void AFireball::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this,&AFireball::OnOverlap);
	SpawnerCharacter = Cast<AProjetSpecialCharacter>(GetInstigator());
	
}

// Called every frame
void AFireball::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

