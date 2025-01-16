// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviorTreeTasksAndDecorators/BTD_IsWithinShootingDistance.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Decorators/BTDecorator_Blackboard.h"
#include "BehaviorTree/Decorators/BTDecorator_BlueprintBase.h"

UBTD_IsWithinShootingDistance::UBTD_IsWithinShootingDistance()
{
	NodeName="Is Within Shooting Distance";
}

bool UBTD_IsWithinShootingDistance::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory) const
{
	APawn* PossessedNPC=OwnerComp.GetAIOwner()->GetPawn();
	AActor* Player=Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Player"));
	float ShootingDistance=OwnerComp.GetBlackboardComponent()->GetValueAsFloat("ShootingDistance");
	if (!Player||!PossessedNPC||ShootingDistance==0)
		return false;
	return FVector::Dist(Player->GetActorLocation(),PossessedNPC->GetActorLocation())<=ShootingDistance;
}
