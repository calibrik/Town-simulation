// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/SpawnPoint.h"

#include "SpeedrunShooterCharacter.h"
#include "AI/NPCBase.h"
#include "Components/CivilianHiveMind.h"
#include "Components/RangeEnemyHiveMind.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
TQueue<ANPCBase*> ASpawnPoint::SpawnQueue;
// Sets default values
ASpawnPoint::ASpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Mesh=CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SpawnRate=3;
	bPatrolRouteDirection=true;
	SetRootComponent(Mesh);
}

void ASpawnPoint::SpawnNPC()
{
	if (SpawnQueue.IsEmpty()||Player->IsActorBeingSeenByPlayer(this)||URangeEnemyHiveMind::S->GetState()==Vigilant||UCivilianHiveMind::S->GetState()==Vigilant)
		return;
	ANPCBase* NPC=*SpawnQueue.Peek();
	SpawnQueue.Pop();
	NPC->SetActorLocation(GetActorLocation());
	NPC->GetMesh()->SetVisibility(true);
	NPC->GetCharacterMovement()->GravityScale=1;
	NPC->SetPatrolRoute(PatrolRoute);
	NPC->SetPatrolRouteDirection(bPatrolRouteDirection);
	NPC->StartAIController();
	NPC->SetControllerState(Patroling,false);
}

// Called when the game starts or when spawned
void ASpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	Mesh->SetVisibility(false);
	Player=Cast<ASpeedrunShooterCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	GetWorldTimerManager().SetTimer(SpawnHandle,this,&ASpawnPoint::SpawnNPC,SpawnRate,true);
}

ASpawnPoint::~ASpawnPoint()
{
	SpawnQueue.Empty();
}


