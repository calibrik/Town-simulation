// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviorTreeTasksAndDecorators/BTT_AttackPlayer.h"

#include "SpeedrunShooterCharacter.h"
#include "AI/NPCBaseAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTT_AttackPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ANPCBaseAIController* EnemyAIController=Cast<ANPCBaseAIController>(OwnerComp.GetAIOwner());
	ASpeedrunShooterCharacter* Player=Cast<ASpeedrunShooterCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(BlackboardKey.SelectedKeyName));
	UE_LOG(LogTemp,Log,TEXT("Attack Player"));
	FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

UBTT_AttackPlayer::UBTT_AttackPlayer(FObjectInitializer const& ObjectInit)
{
	NodeName="Attack Player";
}
