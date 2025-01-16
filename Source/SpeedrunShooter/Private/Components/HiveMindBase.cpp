// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HiveMindBase.h"

#include "Actors/SpawnPoint.h"
#include "AI/NPCBase.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values for this component's properties
UHiveMindBase::UHiveMindBase()
{
	PrimaryComponentTick.bCanEverTick = false;
	State=Peaceful;
}

void UHiveMindBase::OnNPCDied()
{
	SpawnNPCInPool();
}

void UHiveMindBase::SetState(EHiveMindState NewState)
{
	State=NewState;
	OnChangeState.Broadcast(NewState);
}

void UHiveMindBase::SpawnNPCInPool()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride=ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	ANPCBase* NPC=GetWorld()->SpawnActor<ANPCBase>(NPCClass,FVector(0,0,-1000),FRotator::ZeroRotator,SpawnParams);
	NPC->StopAIController();
	ASpawnPoint::SpawnQueue.Enqueue(NPC);
	NPC->GetMesh()->SetVisibility(false);
	NPC->GetCharacterMovement()->GravityScale=0;
}


