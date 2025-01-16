// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviorTreeTasksAndDecorators/BTT_GetClosestPatrolPoint.h"

#include "AI/NPCBase.h"
#include "AIController.h"
#include "Actors/PatrolRoute.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UBTT_GetClosestPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ANPCBase* PossessedPawn=Cast<ANPCBase>(OwnerComp.GetAIOwner()->GetPawn());
	APatrolRoute* PatrolRoute=PossessedPawn->GetPatrolRoute();
	if (PossessedPawn->GetPatrolRouteIndex()!=-10)
	{
		FinishLatentTask(OwnerComp,EBTNodeResult::Failed);
		return EBTNodeResult::Failed;
	}
	TArray<FVector> Points;
	PatrolRoute->GetAllPointsWorldPosition(Points);
	uint8 CurrMinIndex=0;
	float MinDist=FVector::Dist(PossessedPawn->GetActorLocation(),Points[0]);
	for (uint8 i=1;i<Points.Num();i++)
	{
		float Dist=FVector::Dist(PossessedPawn->GetActorLocation(),Points[i]);
		if (Dist<MinDist)
		{
			CurrMinIndex=i;
			MinDist=Dist;
		}
	}
	UE_LOG(LogTemp,Log,TEXT("found %d"),CurrMinIndex);
	PossessedPawn->SetPatrolRouteIndex(CurrMinIndex);
	FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

UBTT_GetClosestPatrolPoint::UBTT_GetClosestPatrolPoint()
{
	NodeName="Get Closest Patrol Point";
}
