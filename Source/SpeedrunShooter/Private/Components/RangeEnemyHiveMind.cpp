// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/RangeEnemyHiveMind.h"

#include "AI/RangeEnemy.h"
#include "Kismet/GameplayStatics.h"


URangeEnemyHiveMind* URangeEnemyHiveMind::S=nullptr;

URangeEnemyHiveMind::URangeEnemyHiveMind()
{
	FindPlayerTimeout=20;
	RangeEnemiesSeeingPlayerAmount=0;
}

void URangeEnemyHiveMind::StartFindPlayerTimer()
{
	GetWorld()->GetTimerManager().ClearTimer(FindPlayerTimeoutHandle);
	GetWorld()->GetTimerManager().SetTimer(FindPlayerTimeoutHandle,[this]()
	{
		SetState(Peaceful);
	},FindPlayerTimeout,false);
}

void URangeEnemyHiveMind::BeginPlay()
{
	Super::BeginPlay();
	check(!S);
	S=this;
	TArray<AActor*> SpawnedEnemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),ARangeEnemy::StaticClass(),SpawnedEnemies);
	int LeftToSpawn=MaxNPCAmount-SpawnedEnemies.Num();
	for (int i=0;i<LeftToSpawn;i++)
	{
		SpawnNPCInPool();
	}
}

void URangeEnemyHiveMind::OnPlayerSeen()
{
	if (State!=Vigilant)
	{
		SetState(Vigilant);
	}
	RangeEnemiesSeeingPlayerAmount++;
}

void URangeEnemyHiveMind::OnNPCDied()
{
	Super::OnNPCDied();
	OnPlayerLost();
}

void URangeEnemyHiveMind::OnPlayerLost()
{
	if (--RangeEnemiesSeeingPlayerAmount==0)
		StartFindPlayerTimer();
}

URangeEnemyHiveMind::~URangeEnemyHiveMind()
{
	S=nullptr;
}

