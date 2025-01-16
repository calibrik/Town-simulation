// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviorTreeTasksAndDecorators/BTT_ChangeState.h"

#include "AI/NPCBaseAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTT_ChangeState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Cast<ANPCBaseAIController>(OwnerComp.GetAIOwner())->SetState(State);
	FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

UBTT_ChangeState::UBTT_ChangeState()
{
	NodeName="Change State";
}
