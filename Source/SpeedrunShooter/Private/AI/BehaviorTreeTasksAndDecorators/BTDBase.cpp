// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviorTreeTasksAndDecorators/BTDBase.h"

UBTDBase::UBTDBase()
{
	bNotifyTick=true;
}

void UBTDBase::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (FlowAbortMode==EBTFlowAbortMode::None)
	{
		bNotifyTick=false;
		return;
	}
	
	if ((FlowAbortMode==EBTFlowAbortMode::Both||FlowAbortMode==EBTFlowAbortMode::LowerPriority)&&CalculateRawConditionValue(OwnerComp,nullptr))
	{
		OwnerComp.RequestBranchActivation(*this, false);
		return;
	}
	if ((FlowAbortMode==EBTFlowAbortMode::Both||FlowAbortMode==EBTFlowAbortMode::Self)&&!CalculateRawConditionValue(OwnerComp,nullptr))
	{
		OwnerComp.RequestBranchDeactivation(*this);
		return;
	}
}
