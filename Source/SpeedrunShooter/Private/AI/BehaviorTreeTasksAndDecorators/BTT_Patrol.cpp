// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviorTreeTasksAndDecorators/BTT_Patrol.h"

#include "AIController.h"
#include "Actors/PatrolRoute.h"
#include "AI/NPCBase.h"
#include "AI/NPCBaseAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "Navigation/PathFollowingComponent.h"


UBTT_Patrol::UBTT_Patrol()
{
	NodeName="Patrol";
	WaitTime=0;
	// bCreateNodeInstance=true;
}

EBTNodeResult::Type UBTT_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AIController=Cast<ANPCBaseAIController>(OwnerComp.GetAIOwner());
	OwnerComponent=&OwnerComp;
	ANPCBase* PossesedNPC=Cast<ANPCBase>(OwnerComp.GetAIOwner()->GetPawn());
	APatrolRoute* PatrolRoute=PossesedNPC->GetPatrolRoute();
	if (!PatrolRoute)
		return EBTNodeResult::Failed;
	FVector Location=PatrolRoute->GetPointWorldPosition(PossesedNPC->GetPatrolRouteIndex());
	PossesedNPC->IncrementPatrolRouteIndex();
	FAIMoveRequest MoveReq(Location);
	MoveReq.SetAllowPartialPath(true);
	MoveReq.SetAllowPartialPath(true);
	MoveReq.SetAcceptanceRadius(100);
	AIController->MoveTo(MoveReq);
	AIController->ReceiveMoveCompleted.AddDynamic(this,&UBTT_Patrol::OnMoveCompleted);
	return EBTNodeResult::InProgress;
}

void UBTT_Patrol::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	AIController->ReceiveMoveCompleted.RemoveDynamic(this, &UBTT_Patrol::OnMoveCompleted);
	if (Result == EPathFollowingResult::Success)
	{
		if (WaitTime>0)
		{
			FTimerHandle WaitHandle;
			GetWorld()->GetTimerManager().SetTimer(WaitHandle,[this]()
			{
				this->FinishLatentTask(*this->OwnerComponent, EBTNodeResult::Succeeded);
			},WaitTime,false);
		}
		else
		{
			this->FinishLatentTask(*this->OwnerComponent, EBTNodeResult::Succeeded);
		}
	}
	else
	{
		UE_LOG(LogTemp,Warning,TEXT("Patrol failed"));
		this->FinishLatentTask(*this->OwnerComponent, EBTNodeResult::Failed);
	}
}
