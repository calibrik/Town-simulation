// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/AIWeapon.h"

#include "Actors/BulletProjectile.h"
#include "AI/RangeEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AISense_Hearing.h"

void AAIWeapon::AttachWeapon(ARangeEnemy* NewOwner)
{
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);
	AttachToComponent(NewOwner->GetMesh(), AttachmentRules, FName(TEXT("GunGripSocket")));
	GunOwnerNPC=NewOwner;
	SkeletalRifleMesh->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	GunOwnerNPC->GetMesh()->GetAnimInstance()->OnMontageEnded.AddDynamic(this,&AAIWeapon::OnAnimEndedBroadcast);
	GunOwnerNPC->GetMesh()->GetAnimInstance()->OnPlayMontageNotifyBegin.AddDynamic(this,&AAIWeapon::Fire);
}

void AAIWeapon::StartFire(AActor* Target)
{
	if (!FireAnimation)
		return;

	CurrTarget=Target;
	UAnimInstance* AnimInstance = GunOwnerNPC->GetMesh()->GetAnimInstance();
	if (AnimInstance != nullptr)
	{
		AnimInstance->Montage_Play(FireAnimation, 1.f);
	}
}

void AAIWeapon::BeginPlay()
{
	
}

void AAIWeapon::OnAnimEndedBroadcast(UAnimMontage* Montage, bool bInterrupted)
{
	if (Montage==FireAnimation)
		OnAnimEnded.ExecuteIfBound();
}

void AAIWeapon::Fire(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	if (NotifyName!="Fire")
		return;
	
	FVector TraceStart{GetActorLocation()+GunOwnerNPC->GetActorRotation().RotateVector(MuzzleOffset)};
	FVector TraceEnd{TraceStart+(CurrTarget->GetActorLocation()-TraceStart).GetSafeNormal()*ShootingDistance};
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.AddIgnoredActor(GunOwnerNPC);
	FHitResult ResultHit;
	// const FRotator SpawnRotation = Cast<APlayerController>(Character->GetController())->PlayerCameraManager->GetCameraRotation();
	if (GetWorld()->LineTraceSingleByChannel(ResultHit,TraceStart,TraceEnd,ECC_Camera,QueryParams))
	{
		TraceEnd=ResultHit.Location;
		// if (ASpeedrunShooterCharacter* Player=Cast<ASpeedrunShooterCharacter>(ResultHit.GetActor()))
		// 	Player->Damage(Damage);
		// if (FireVFXClass&&ExplosionVFXClass)
		// {
		// 	FActorSpawnParameters VFXSpawnParams;
		// 	VFXSpawnParams.Instigator=GunOwnerNPC;
		// 	VFXSpawnParams.Owner=this;
		// 	const FRotator Rotation=FRotator(0,0,0);
		// 	GetWorld()->SpawnActor<AVFXActor>(FireVFXClass,TraceEnd,Rotation,VFXSpawnParams);
		// 	GetWorld()->SpawnActor<AVFXActor>(ExplosionVFXClass,TraceEnd,Rotation,VFXSpawnParams);
		// }
	}
	// DrawDebugLine(GetWorld(),TraceStart,TraceEnd,FColor::Red,false,1,0,3);
	if (BulletClass)
	{
		FActorSpawnParameters ActorSpawnParams;
		// ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		FRotator Rotation = (TraceEnd-TraceStart).ToOrientationRotator();
		ABulletProjectile* Bullet=GetWorld()->SpawnActor<ABulletProjectile>(BulletClass, TraceStart, Rotation, ActorSpawnParams);
		if (Bullet)
			Bullet->SetDamage(Damage);
	}
	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireSound, GunOwnerNPC->GetActorLocation());
		UAISense_Hearing::ReportNoiseEvent(GetWorld(),GunOwnerNPC->GetActorLocation(),1,GunOwnerNPC);
	}
}
