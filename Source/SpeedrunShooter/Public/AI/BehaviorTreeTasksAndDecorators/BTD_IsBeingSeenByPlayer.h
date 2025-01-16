// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/BehaviorTreeTasksAndDecorators/BTDBase.h"
#include "BTD_IsBeingSeenByPlayer.generated.h"

/**
 * 
 */
UCLASS()
class SPEEDRUNSHOOTER_API UBTD_IsBeingSeenByPlayer : public UBTDBase
{
	GENERATED_BODY()

protected:
	UBTD_IsBeingSeenByPlayer();
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
