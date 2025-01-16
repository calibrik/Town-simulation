// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "NPCBaseAIController.generated.h"

class ASpeedrunShooterCharacter;
struct FActorPerceptionUpdateInfo;
class UBlackboardComponent;
class UBehaviorTreeComponent;
class UBehaviorTree;
class UAIPerceptionComponent;

UENUM()
enum ENPCState:uint8
{
	Aggressive UMETA(DisplayName="Aggressive"),
	Investigating UMETA(DisplayName="Investigating"),
	Hiding UMETA(DisplayName="Hiding"),
	Patroling UMETA(DisplayName="Patroling"),
	Frozen UMETA(DisplayName="Frozen"),
};

/**
 * 
 */
UCLASS()
class SPEEDRUNSHOOTER_API ANPCBaseAIController : public AAIController
{
	GENERATED_BODY()
public:
	ANPCBaseAIController();
	UBlackboardComponent* GetBlackboard() const {return TreeComponent->GetBlackboardComponent();}
protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	UPROPERTY(EditDefaultsOnly,Category="My settings|AI")
	UBehaviorTreeComponent* TreeComponent;
	UPROPERTY(EditDefaultsOnly,Category="My settings|AI")
	UBehaviorTree* Tree;
	UPROPERTY(EditDefaultsOnly,Category="My settings|AI")
	UAIPerceptionComponent* AIPerceptionComponent;
	ENPCState State;
	UPROPERTY(EditDefaultsOnly,Category="My settings|Speed")
	float WalkingSpeed;
	UPROPERTY(EditDefaultsOnly,Category="My settings|Speed")
	float RunningSpeed;
	// UPROPERTY(EditDefaultsOnly,Category="AI")
	// UBlackboardComponent* BlackboardComponent;
public:
	ENPCState GetState() const;
	UFUNCTION()
	virtual void OnTargetPerceptionInfoUpdated_Delegate(const FActorPerceptionUpdateInfo& UpdateInfo);
	void StopAI();
	void StartAI();
	virtual void SetState(ENPCState NewState,bool bProcessPrevState=true);
	//virtual void ActorsPerceptionUpdated(const TArray<AActor*>& UpdatedActors) override;
};
