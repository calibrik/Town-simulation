// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponBase.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	MuzzleOffset = FVector(100.0f, 0.0f, 10.0f);
	SkeletalRifleMesh=CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalRifleMesh"));
	ShootingDistance=10000;
	PunchPower=4;
	SetRootComponent(SkeletalRifleMesh);
	RecoilPunchPower=5;
	Damage=20;
}
void AWeaponBase::DetachWeapon()
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	SkeletalRifleMesh->SetSimulatePhysics(true);
	SkeletalRifleMesh->SetCollisionObjectType(ECC_WorldDynamic);
	SkeletalRifleMesh->SetCollisionEnabled(ECollisionEnabled::Type::QueryAndPhysics);
	SkeletalRifleMesh->SetCollisionProfileName("Ragdoll");
	SkeletalRifleMesh->SetEnableGravity(true);
}
