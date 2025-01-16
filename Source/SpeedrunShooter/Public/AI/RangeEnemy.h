// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/NPCBase.h"
#include "RangeEnemy.generated.h"

class AAIWeapon;
/**
 * 
 */
UCLASS()
class SPEEDRUNSHOOTER_API ARangeEnemy : public ANPCBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly,Category="Gun")
	TSubclassOf<AAIWeapon> WeaponClass;
	UPROPERTY()
	AAIWeapon* Weapon;
	
	virtual void BeginPlay() override;
public:
	ARangeEnemy();

protected:
	virtual void UnFreeze(UAnimMontage* Montage, bool bInterrupted) override;

public:
	virtual void Die() override;
	FORCEINLINE AAIWeapon* GetWeapon() const {return Weapon;}
};
