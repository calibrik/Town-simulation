// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDBase.generated.h"

/**
 * 
 */
UCLASS()
class SPEEDRUNSHOOTER_API UBTDBase : public UBTDecorator
{
	GENERATED_BODY()

protected:
	UBTDBase();
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
