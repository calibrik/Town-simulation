// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_ChasePlayer.generated.h"

/**
 * 
 */
UCLASS()
class SPEEDRUNSHOOTER_API UBTT_ChasePlayer : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTT_ChasePlayer(FObjectInitializer const& ObjectInit);
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
