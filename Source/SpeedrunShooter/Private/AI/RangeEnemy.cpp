// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/RangeEnemy.h"

#include "AI/RangeEnemyAIConttroller.h"
#include "Components/RangeEnemyHiveMind.h"
#include "Weapon/AIWeapon.h"

void ARangeEnemy::BeginPlay()
{
	Super::BeginPlay();
	FActorSpawnParameters WeaponSpawnParams;
	WeaponSpawnParams.Owner=this;
	Weapon=GetWorld()->SpawnActor<AAIWeapon>(WeaponClass,FVector::Zero(),FRotator::ZeroRotator,WeaponSpawnParams);
	Weapon->AttachWeapon(this);
	ARangeEnemyAIConttroller* MyController=Cast<ARangeEnemyAIConttroller>(GetController());
	MyController->SetShootingDistance(Weapon->GetShootingDistance());
	// TArray<AActor*> Floors;
	// UGameplayStatics::GetAllActorsWithTag(GetWorld(),"floor",Floors);
	// URangeEnemyHiveMind* HiveMind=Floors[0]->FindComponentByClass<URangeEnemyHiveMind>();
	// if (HiveMind)
	// 	Cast<ARangeEnemyAIConttroller>(AIController)->SetHiveMind(HiveMind);
}

ARangeEnemy::ARangeEnemy()
{

}

void ARangeEnemy::UnFreeze(UAnimMontage* Montage, bool bInterrupted)
{
	if (Montage==HitAnim&&!bInterrupted)
		AIController->SetState(Aggressive);
}

void ARangeEnemy::Die()
{
	Super::Die();
	Weapon->DetachWeapon();
	URangeEnemyHiveMind::S->OnNPCDied();
}


