// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviorTreeTasksAndDecorators/BTD_IsBeingSeenByPlayer.h"

#include "AIController.h"
#include "SpeedrunShooterCharacter.h"
#include "AI/NPCBase.h"
#include "Kismet/GameplayStatics.h"

UBTD_IsBeingSeenByPlayer::UBTD_IsBeingSeenByPlayer()
{
	NodeName="Is NPC Being Seen By Player";
}

bool UBTD_IsBeingSeenByPlayer::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	ANPCBase* PossesedNPC = Cast<ANPCBase>(OwnerComp.GetAIOwner()->GetPawn());
	ASpeedrunShooterCharacter* Player=Cast<ASpeedrunShooterCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	// if (ACivilian* Civilian=Cast<ACivilian>(PossesedNPC))
	// 	Cast<ACivilianAIController>(Civilian->GetController())->ResetHidingTimer();
	return Player->IsActorBeingSeenByPlayer(PossesedNPC);
}
