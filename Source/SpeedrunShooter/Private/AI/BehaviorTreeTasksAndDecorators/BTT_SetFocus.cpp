// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviorTreeTasksAndDecorators/BTT_SetFocus.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTT_SetFocus::UBTT_SetFocus()
{
	NodeName="Set Focus";
}

EBTNodeResult::Type UBTT_SetFocus::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AActor* Player=Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(FocusTargetKey.SelectedKeyName));
	OwnerComp.GetAIOwner()->SetFocus(Player);
	FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
