// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/VFXActor.h"

#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AVFXActor::AVFXActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	LiveTime=0;
	ParticleSystemComponent=CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle System"));
	SphereForNav=CreateDefaultSubobject<USphereComponent>(TEXT("Sphere For Nav"));
	SphereForNav->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SphereForNav->SetCanEverAffectNavigation(true);
	SphereForNav->bDynamicObstacle=true;
	SetRootComponent(ParticleSystemComponent);
}

// Called when the game starts or when spawned
void AVFXActor::BeginPlay()
{
	Super::BeginPlay();
	SphereForNav->SetCanEverAffectNavigation(bShouldAffectNavigation);
	// UParticleSystemComponent* ParticleSystem=GetComponentByClass<UParticleSystemComponent>();
	ParticleSystemComponent->OnSystemFinished.AddDynamic(this,&AVFXActor::OnParticleSystemFinished);
	// USphereComponent* SphereComponent=GetComponentByClass<USphereComponent>();
	if (LiveTime>0)
	{
		FTimerHandle DestroyHandle;
		GetWorldTimerManager().SetTimer(DestroyHandle,[this]()
		{
			ParticleSystemComponent->Deactivate();
			if (bShouldAffectNavigation) SphereForNav->SetCanEverAffectNavigation(false);
			// Destroy();
		},LiveTime,false);
	}
}

void AVFXActor::OnParticleSystemFinished(UParticleSystemComponent* PSystem)
{
	Destroy();
}


