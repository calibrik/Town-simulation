// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviorTreeTasksAndDecorators/BTT_ClearFocus.h"

#include "AIController.h"

UBTT_ClearFocus::UBTT_ClearFocus()
{
	NodeName="Clear Focus";
}

EBTNodeResult::Type UBTT_ClearFocus::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwnerComp.GetAIOwner()->ClearFocus(EAIFocusPriority::Gameplay);
	FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
