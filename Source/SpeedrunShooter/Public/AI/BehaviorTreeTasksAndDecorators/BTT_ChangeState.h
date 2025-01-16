// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_ChangeState.generated.h"

enum ENPCState : uint8;
/**
 * 
 */
UCLASS()
class SPEEDRUNSHOOTER_API UBTT_ChangeState : public UBTTaskNode
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere)
	TEnumAsByte<ENPCState> State;
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	UBTT_ChangeState();
};
