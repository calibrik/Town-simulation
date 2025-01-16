// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Civilian.h"

#include "AI/CivilianAIController.h"
#include "Components/CivilianHiveMind.h"
#include "Kismet/GameplayStatics.h"

void ACivilian::UnFreeze(UAnimMontage* Montage, bool bInterrupted)
{
	if (Montage==HitAnim&&!bInterrupted)
		AIController->SetState(Hiding);
}

void ACivilian::Freeze()
{
	Super::Freeze();
	Cast<ACivilianAIController>(AIController)->OnPlayerShoot();
}

void ACivilian::BeginPlay()
{
	Super::BeginPlay();
}

void ACivilian::Die()
{
	Super::Die();
	UCivilianHiveMind::S->OnNPCDied();
}
