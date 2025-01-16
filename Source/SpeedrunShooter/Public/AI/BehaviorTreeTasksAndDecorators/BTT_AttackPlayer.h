﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTT_AttackPlayer.generated.h"

/**
 * 
 */
UCLASS()
class SPEEDRUNSHOOTER_API UBTT_AttackPlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	UBTT_AttackPlayer(FObjectInitializer const& ObjectInit);
};
