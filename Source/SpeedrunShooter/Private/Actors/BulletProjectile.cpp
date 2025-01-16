// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/BulletProjectile.h"

#include "NiagaraComponent.h"
#include "SpeedrunShooterCharacter.h"
#include "AI/NPCBase.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
ABulletProjectile::ABulletProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	NiagaraComponent=CreateDefaultSubobject<UNiagaraComponent>("Niagara");
	RadialForceComponent=CreateDefaultSubobject<URadialForceComponent>("Radial Force");
	ProjectileMovementComponent=CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Movement");
	RadialForceComponent->SetupAttachment(NiagaraComponent);
	BoxCollider=CreateDefaultSubobject<UBoxComponent>("Collider");
	SetRootComponent(NiagaraComponent);
	BoxCollider->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndProbe);
	BoxCollider->SetupAttachment(RootComponent);
	DestroyTime=10;
}

// Called when the game starts or when spawned
void ABulletProjectile::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle DestroyHandle;
	GetWorldTimerManager().SetTimer(DestroyHandle,[this]()
	{
		if (this)
			Destroy();
	},DestroyTime,false);
}

void ABulletProjectile::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp,
	bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);
	RadialForceComponent->FireImpulse();
	if (ANPCBase* NPC=Cast<ANPCBase>(Other))
	{
		NPC->Damage(Damage);
	}
	if (ASpeedrunShooterCharacter* Player=Cast<ASpeedrunShooterCharacter>(Other))
	{
		Player->Damage(Damage);
	}
	Destroy();
}

void ABulletProjectile::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if (ANPCBase* NPC=Cast<ANPCBase>(OtherActor))
	{
		NPC->Damage(Damage);
		if (!NPC->IsAlive())
			RadialForceComponent->FireImpulse();
	}
	if (ASpeedrunShooterCharacter* Player=Cast<ASpeedrunShooterCharacter>(OtherActor))
	{
		Player->Damage(Damage);
	}
	Destroy();
}


