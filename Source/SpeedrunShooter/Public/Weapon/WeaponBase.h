// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

class ABulletProjectile;
class AVFXActor;

UCLASS()
class SPEEDRUNSHOOTER_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();

protected:
	/** Projectile class to spawn */
	// UPROPERTY(EditDefaultsOnly, Category=Projectile)
	// TSubclassOf<class ASpeedrunShooterProjectile> ProjectileClass;
	UPROPERTY(EditDefaultsOnly,Category="Mesh")
	USkeletalMeshComponent* SkeletalRifleMesh;
	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USoundBase* FireSound;
	
	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="My settings|Shooting")
	FVector MuzzleOffset;
	
	UPROPERTY(EditAnywhere,Category="My settings|Shooting")
	float ShootingDistance;
	UPROPERTY(EditDefaultsOnly,Category="My settings")
	TSubclassOf<ABulletProjectile> BulletClass;
	UPROPERTY(EditAnywhere,Category="My settings|Shooting")
	float PunchPower;
	UPROPERTY(EditAnywhere,Category="My settings|Shooting")
	float RecoilPunchPower;
	UPROPERTY(EditAnywhere,Category="My settings|Shooting")
	float Damage;
public:
	virtual void DetachWeapon();

};
