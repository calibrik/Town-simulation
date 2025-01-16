// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_GetClosestPatrolPoint.generated.h"

/**
 * 
 */
UCLASS()
class SPEEDRUNSHOOTER_API UBTT_GetClosestPatrolPoint : public UBTTaskNode
{
	GENERATED_BODY()
	
	// UPROPERTY(EditAnywhere)
	// FBlackboardKeySelector CurrentPatrolIndexKey;

public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	UBTT_GetClosestPatrolPoint();
};
