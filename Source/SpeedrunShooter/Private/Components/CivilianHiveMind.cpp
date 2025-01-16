// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CivilianHiveMind.h"

#include "AI/Civilian.h"
#include "Kismet/GameplayStatics.h"

UCivilianHiveMind* UCivilianHiveMind::S=nullptr;

// Sets default values for this component's properties
UCivilianHiveMind::UCivilianHiveMind()
{
	HidingTime=20;
}

void UCivilianHiveMind::BeginPlay()
{
	Super::BeginPlay();
	check(!S);
	S=this;
	TArray<AActor*> SpawnedCivilians;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),ACivilian::StaticClass(),SpawnedCivilians);
	int LeftToSpawn=MaxNPCAmount-SpawnedCivilians.Num();
	for (int i=0;i<LeftToSpawn;i++)
	{
		SpawnNPCInPool();
	}
}

void UCivilianHiveMind::StartHidingTimer()
{
	GetWorld()->GetTimerManager().SetTimer(HidingTimerHandle,[this]()
	{
		SetState(Peaceful);
	},HidingTime,false);
}

void UCivilianHiveMind::ResetHidingTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(HidingTimerHandle);
	StartHidingTimer();
}

UCivilianHiveMind::~UCivilianHiveMind()
{
	S=nullptr;
}

void UCivilianHiveMind::OnShoot()
{
	if (State==Vigilant)
	{
		ResetHidingTimer();
		return;
	}
	SetState(Vigilant);
	StartHidingTimer();
}

