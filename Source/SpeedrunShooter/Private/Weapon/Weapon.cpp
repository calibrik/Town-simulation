// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Weapon.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "SpeedrunShooterCharacter.h"
#include "SpeedrunShooterPlayerController.h"
#include "Actors/BulletProjectile.h"
#include "Actors/VFXActor.h"
#include "AI/RangeEnemy.h"
#include "Perception/AISense_Hearing.h"

// Sets default values
AWeapon::AWeapon()
{
	
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AWeapon::Setup(ASpeedrunShooterCharacter* NewOwner)
{
	if (!GunOwner)
	{
		GunOwner=NewOwner;
		if (APlayerController* PlayerController = Cast<APlayerController>(GunOwner->GetController()))
		{
			if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
			{
				// Fire
				EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &AWeapon::Fire);
			}
		}
	}
	SkeletalRifleMesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	HideWeapon();
}

void AWeapon::HideWeapon()
{
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Cast<ASpeedrunShooterPlayerController>(GunOwner->GetController())->GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->RemoveMappingContext(WeaponMappingContext);
	}
	GunOwner->SetHasRifle(false);
	DetachFromActor(FDetachmentTransformRules(EDetachmentRule::KeepWorld,true));
	SetActorLocation(FVector(0,0,-3000));
	SkeletalRifleMesh->SetVisibility(false);
}

void AWeapon::ShowWeapon()
{
	SkeletalRifleMesh->SetVisibility(true);
	// Attach the weapon to the First Person Character
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(GunOwner->GetMesh1P(), AttachmentRules, FName(TEXT("GripPoint")));
	GunOwner->SetHasRifle(true);
	// Set up action bindings
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(Cast<ASpeedrunShooterPlayerController>(GunOwner->GetController())->GetLocalPlayer()))
	{
		// add the mapping context so we get controls
		Subsystem->AddMappingContext(WeaponMappingContext, 1);
	}
}

void AWeapon::Fire()
{
	if (!GunOwner)
	{
		return;
	}

	// Try and fire a projectile
	// if (ProjectileClass)
	// {
	// 	if (UWorld* const World = GetWorld())
	// 	{
	// 		APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
	// 		const FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
	// 		// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
	// 		const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(MuzzleOffset);
	//
	// 		//Set Spawn Collision Handling Override
	// 		FActorSpawnParameters ActorSpawnParams;
	// 		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
	//
	// 		// Spawn the projectile at the muzzle
	// 		World->SpawnActor<ASpeedrunShooterProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
	// 	}
	// }
	
	FVector TraceStart{GunOwner->GetCameraPos()};
	FVector TraceEnd{TraceStart+GunOwner->GetCameraForwardVector()*ShootingDistance};
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.AddIgnoredActor(GunOwner);
	FHitResult ResultHit;
	// const FRotator SpawnRotation = Cast<APlayerController>(Character->GetController())->PlayerCameraManager->GetCameraRotation();
	FVector TraceStartFX{GetActorLocation() +GunOwner->GetCameraRotation().RotateVector(MuzzleOffset)};
	FVector TraceEndFX{0};
	if (GetWorld()->LineTraceSingleByChannel(ResultHit,TraceStart,TraceEnd,ECC_Camera,QueryParams))
	{
		TraceEndFX=ResultHit.Location;
		// FActorSpawnParameters VFXSpawnParams;
		// VFXSpawnParams.Instigator=GunOwner;
		// VFXSpawnParams.Owner=this;
		// const FRotator Rotation=FRotator(0,0,0);
		// if (ANPCBase* NPC=Cast<ANPCBase>(ResultHit.GetActor()))
		// {
		// 	NPC->Damage(Damage);
		// 	if (NPCHitVFXClass)
		// 		GetWorld()->SpawnActor<AVFXActor>(NPCHitVFXClass,TraceEndFX,(TraceStart-TraceEndFX).Rotation(),VFXSpawnParams);
		// }
		// else
		// {
		// 	if (ConcreteHitVFXClass)
		// 		GetWorld()->SpawnActor<AVFXActor>(ConcreteHitVFXClass,TraceEndFX,Rotation,VFXSpawnParams);
		// }
		// if (ResultHit.Component->IsSimulatingPhysics())
		// {
		// 	ResultHit.Component->AddImpulseAtLocation(PunchPower*(TraceEnd-TraceStart).GetUnsafeNormal(), ResultHit.Location);//(1-ShootingDistance/ResultHit.GetActor()->GetDistanceTo(this))*
		// 	// UE_LOG(LogTemp,Log,TEXT("Name: %s Distance: %f"),*ResultHit.GetActor()->GetName(),ResultHit.GetActor()->GetDistanceTo(this));
		// }
		// if (FireVFXClass&&ExplosionVFXClass)
		// {
		// 	GetWorld()->SpawnActor<AVFXActor>(FireVFXClass,TraceEndFX,Rotation,VFXSpawnParams);
		// 	GetWorld()->SpawnActor<AVFXActor>(ExplosionVFXClass,TraceEndFX,Rotation,VFXSpawnParams);
		// }
	}
	else
	{
		TraceEndFX=TraceStart+GunOwner->GetCameraForwardVector()*ShootingDistance;
	}
	
	// DrawDebugLine(GetWorld(),TraceStart,TraceEndFX,FColor::Orange,false,1,0,3);
	// DrawDebugLine(GetWorld(),TraceStartFX,TraceEndFX,FColor::Green,false,1,0,3);
	// FVector Impulse=(TraceStart-TraceEnd).GetUnsafeNormal()*RecoilPunchPower;
	// Character->LaunchCharacter(Impulse,false,false);
	if (BulletClass)
	{
		FActorSpawnParameters ActorSpawnParams;
		// ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		FRotator Rotation = (TraceEndFX-TraceStartFX).ToOrientationRotator();
		ABulletProjectile* Bullet=GetWorld()->SpawnActor<ABulletProjectile>(BulletClass, TraceStartFX, Rotation, ActorSpawnParams);
		if (Bullet)
			Bullet->SetDamage(Damage);
	}
	// Try and play the sound if specified
	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GunOwner->GetActorLocation());
		UAISense_Hearing::ReportNoiseEvent(GetWorld(),GunOwner->GetActorLocation(),1,GunOwner);
	}
	
	// Try and play a firing animation if specified
	if (FireAnimation)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = GunOwner->GetMesh1P()->GetAnimInstance();
		if (AnimInstance != nullptr)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}


