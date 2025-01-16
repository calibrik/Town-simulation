// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviorTreeTasksAndDecorators/BTT_ClearIndex.h"

#include "AIController.h"
#include "Actors/PatrolRoute.h"
#include "AI/NPCBase.h"

UBTT_ClearIndex::UBTT_ClearIndex()
{
	NodeName="Clear Index";
}

EBTNodeResult::Type UBTT_ClearIndex::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ANPCBase* PossessedPawn=Cast<ANPCBase>(OwnerComp.GetAIOwner()->GetPawn());
	APatrolRoute* PatrolRoute=PossessedPawn->GetPatrolRoute();
	PossessedPawn->SetPatrolRouteIndex(-10);
	FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
