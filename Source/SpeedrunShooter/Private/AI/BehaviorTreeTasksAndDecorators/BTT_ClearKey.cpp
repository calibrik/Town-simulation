// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviorTreeTasksAndDecorators/BTT_ClearKey.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTT_ClearKey::UBTT_ClearKey()
{
	NodeName="Clear Key";
}

EBTNodeResult::Type UBTT_ClearKey::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwnerComp.GetAIOwner()->GetBlackboardComponent()->ClearValue(KeyToClear.SelectedKeyName);
	FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
