// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_Patrol.generated.h"

namespace EPathFollowingResult
{
	enum Type : int;
}

class ANPCBaseAIController;

UCLASS()
class SPEEDRUNSHOOTER_API UBTT_Patrol : public UBTTaskNode
{
	GENERATED_BODY()
	
	
	// UPROPERTY(EditAnywhere)
	// FBlackboardKeySelector CurrentPatrolIndexKey;
	// UPROPERTY(EditAnywhere)
	// FBlackboardKeySelector LocationKey;
	// UPROPERTY(EditAnywhere)
	// FBlackboardKeySelector WaitTimeKey;
	// UPROPERTY(EditAnywhere)
	// FBlackboardKeySelector RotationKey;
	UPROPERTY()
	ANPCBaseAIController* AIController;
	UPROPERTY()
	UBehaviorTreeComponent* OwnerComponent;
	UPROPERTY(EditAnywhere)
	float WaitTime;
public:
	UBTT_Patrol();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	UFUNCTION()
	void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result);
};
