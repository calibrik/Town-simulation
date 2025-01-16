// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "SpeedrunShooterCharacter.generated.h"

class AWeapon;
class AShooterHUD;
class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ASpeedrunShooterCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ToggleWeaponAction;
public:
	ASpeedrunShooterCharacter();

protected:
	UPROPERTY()
	AShooterHUD* HUD;
	UPROPERTY(EditAnywhere,Category="Health")
	float MaxHealth;
	float CurrHealth;
	float OldHealth;
	FTimeline RegenTimeline;
	FTimerHandle RegenWaitHandle;
	UPROPERTY(EditAnywhere,Category="Health")
	float RegenWaitTime;
	UPROPERTY(EditAnywhere,Category="Health")
	// float RegenRate;
	UCurveFloat* RegenRateCurve;
	UPROPERTY(EditDefaultsOnly,Category="Weapon")
	TSubclassOf<AWeapon> WeaponClass;
	UPROPERTY()
	AWeapon* Weapon;
	UFUNCTION()
	void Regen(float Value);
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaSeconds) override;
	FORCEINLINE FVector GetCameraForwardVector() const {return FirstPersonCameraComponent->GetForwardVector();}
	FORCEINLINE FVector GetCameraPos() const {return FirstPersonCameraComponent->GetComponentLocation();}
	FORCEINLINE FRotator GetCameraRotation() const {return FirstPersonCameraComponent->GetComponentRotation();}

	/** Bool for AnimBP to switch to another animation set */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Weapon)
	bool bHasRifle;

	/** Setter to set the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	void SetHasRifle(bool bNewHasRifle);

	/** Getter for the bool */
	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool GetHasRifle();

protected:
	void ToggleWeapon();
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface
	void SetHealth(float NewHealth);
public:
	virtual void LaunchCharacter(FVector LaunchVelocity, bool bXYOverride, bool bZOverride) override;
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
	void Damage(float Damage);
	bool IsActorBeingSeenByPlayer(const AActor* Actor) const;
};

