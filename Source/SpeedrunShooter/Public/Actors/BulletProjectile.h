// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BulletProjectile.generated.h"

class AVFXActor;
class UBoxComponent;
class UProjectileMovementComponent;
class URadialForceComponent;
class UNiagaraComponent;

UCLASS()
class SPEEDRUNSHOOTER_API ABulletProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABulletProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly)
	UNiagaraComponent* NiagaraComponent;
	UPROPERTY(EditDefaultsOnly)
	URadialForceComponent* RadialForceComponent;
	UPROPERTY(EditDefaultsOnly)
	UProjectileMovementComponent* ProjectileMovementComponent;
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* BoxCollider;
	float Damage;
	UPROPERTY(EditDefaultsOnly,Category="My settings")
	float DestroyTime;
	UPROPERTY(EditDefaultsOnly,Category="My settings|VFX")
	TSubclassOf<AVFXActor> FireVFXClass;
	
	UPROPERTY(EditDefaultsOnly,Category="My settings|VFX")
	TSubclassOf<AVFXActor> ExplosionVFXClass;
	
	UPROPERTY(EditDefaultsOnly,Category="My settings|VFX")
	TSubclassOf<AVFXActor> ConcreteHitVFXClass;
	
	UPROPERTY(EditDefaultsOnly,Category="My settings|VFX")
	TSubclassOf<AVFXActor> NPCHitVFXClass;

public:
	FORCEINLINE void SetDamage(float NewDamage) {Damage=NewDamage;}
	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved,
		FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
