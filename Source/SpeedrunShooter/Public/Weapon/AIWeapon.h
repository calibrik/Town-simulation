// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/Weapon.h"
#include "AIWeapon.generated.h"

DECLARE_DELEGATE(FOnAnimEnded);

class ARangeEnemy;

/**
 * 
 */
UCLASS()
class SPEEDRUNSHOOTER_API AAIWeapon : public AWeaponBase
{
	GENERATED_BODY()
protected:
	UPROPERTY()
	ARangeEnemy* GunOwnerNPC;
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnAnimEndedBroadcast(UAnimMontage* Montage, bool bInterrupted);
	UPROPERTY()
	AActor* CurrTarget;
	UFUNCTION()
	void Fire(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);

public:
	FOnAnimEnded OnAnimEnded;
	void AttachWeapon(ARangeEnemy* NewOwner);
	void StartFire(AActor* Target);

	FORCEINLINE float GetShootingDistance() const {return ShootingDistance;}
};
