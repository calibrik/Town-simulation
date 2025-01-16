// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"
class UInputMappingContext;
class AVFXActor;
class ASpeedrunShooterCharacter;

UCLASS()
class SPEEDRUNSHOOTER_API AWeapon : public AWeaponBase
{
	GENERATED_BODY()

private:
	UPROPERTY()
	ASpeedrunShooterCharacter* GunOwner;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* FireAction;
	UPROPERTY(EditDefaultsOnly,Category=Input,meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* WeaponMappingContext;
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void Setup(ASpeedrunShooterCharacter* NewOwner);
	void HideWeapon();
	void ShowWeapon();
protected:

	
	/** MappingContext */
	// UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	// class UInputMappingContext* FireMappingContext;

	/** Fire Input Action */


	/** Attaches the actor to a FirstPersonCharacter */


	/** Make the weapon Fire a Projectile */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void Fire();

};

