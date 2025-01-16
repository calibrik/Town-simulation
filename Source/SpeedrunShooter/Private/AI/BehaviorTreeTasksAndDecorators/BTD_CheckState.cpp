// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviorTreeTasksAndDecorators/BTD_CheckState.h"

#include "Actors/PatrolRoute.h"
#include "AI/NPCBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"

UBTD_CheckState::UBTD_CheckState()
{
	NodeName="Check State";
}

bool UBTD_CheckState::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	if (StateTypes.Num()==0)
		return false;
	for (ENPCState StateType:StateTypes)
	{
		ENPCState CurrStateType=static_cast<ENPCState>(OwnerComp.GetBlackboardComponent()->GetValueAsEnum("State"));
		if (CurrStateType==StateType)
			return true;
	}
	return false;
}
