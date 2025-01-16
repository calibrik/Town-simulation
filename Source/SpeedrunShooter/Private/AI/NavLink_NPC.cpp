// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/NavLink_NPC.h"

#include "AI/NPCBase.h"


void ANavLink_NPC::BeginPlay()
{
	Super::BeginPlay();
	OnSmartLinkReached.AddDynamic(this,&ANavLink_NPC::OnSmartLinkReached_Delegate);
}

void ANavLink_NPC::OnSmartLinkReached_Delegate(AActor* MovingActor, const FVector& DestinationPoint)
{
	Cast<ANPCBase>(MovingActor)->JumpTo(DestinationPoint);
}
