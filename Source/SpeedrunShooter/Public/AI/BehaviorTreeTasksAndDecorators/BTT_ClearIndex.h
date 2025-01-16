// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_ClearIndex.generated.h"

/**
 * 
 */
UCLASS()
class SPEEDRUNSHOOTER_API UBTT_ClearIndex : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTT_ClearIndex();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
