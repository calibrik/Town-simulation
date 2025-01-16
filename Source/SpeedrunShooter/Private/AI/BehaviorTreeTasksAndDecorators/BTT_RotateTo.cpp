// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviorTreeTasksAndDecorators/BTT_RotateTo.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTT_RotateTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FRotator Rotation=OwnerComp.GetBlackboardComponent()->GetValueAsRotator(RotationKey.SelectedKeyName);
	OwnerComp.GetAIOwner()->GetPawn()->SetActorRotation(Rotation);
	// OwnerComp.GetAIOwner()->SetControlRotation(Rotation);
	return EBTNodeResult::Succeeded;
}

UBTT_RotateTo::UBTT_RotateTo()
{
	NodeName="Rotate To";
}
