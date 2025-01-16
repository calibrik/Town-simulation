// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BTDBase.h"
#include "AI/NPCBaseAIController.h"
#include "BehaviorTree/Decorators/BTDecorator_Blackboard.h"
#include "BTD_CheckState.generated.h"

/**
 * 
 */
UCLASS()
class SPEEDRUNSHOOTER_API UBTD_CheckState : public UBTDBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere)
 	TArray<TEnumAsByte<ENPCState>> StateTypes;
public:
	UBTD_CheckState();
public:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
