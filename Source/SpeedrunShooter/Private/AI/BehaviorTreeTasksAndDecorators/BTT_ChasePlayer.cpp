// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviorTreeTasksAndDecorators/BTT_ChasePlayer.h"
#include "NavigationSystem.h"
#include "AI/NPCBaseAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTT_ChasePlayer::UBTT_ChasePlayer(FObjectInitializer const& ObjectInit)
{
	NodeName=TEXT("Chase Player");
}

EBTNodeResult::Type UBTT_ChasePlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ANPCBaseAIController* EnemyAIController=Cast<ANPCBaseAIController>(OwnerComp.GetAIOwner());
	AActor* Player=Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Player"));
	if (UNavigationSystemV1::GetCurrent(GetWorld()))
	{
		EnemyAIController->MoveToActor(Player);
		FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	FinishLatentTask(OwnerComp,EBTNodeResult::Failed);
	return EBTNodeResult::Failed;
}
