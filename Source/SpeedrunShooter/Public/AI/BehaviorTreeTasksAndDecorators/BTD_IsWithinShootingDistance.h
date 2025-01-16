// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTDBase.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTD_IsWithinShootingDistance.generated.h"

/**
 * 
 */
UCLASS()
class SPEEDRUNSHOOTER_API UBTD_IsWithinShootingDistance : public UBTDBase
{
	GENERATED_BODY()
protected:
	UBTD_IsWithinShootingDistance();
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
