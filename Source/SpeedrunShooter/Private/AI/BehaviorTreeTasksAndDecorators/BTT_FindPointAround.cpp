// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviorTreeTasksAndDecorators/BTT_FindPointAround.h"

#include "NavigationSystem.h"
#include "AI/NPCBase.h"
#include "AI/NPCBaseAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTT_FindPointAround::UBTT_FindPointAround(FObjectInitializer const& ObjectInit)
{
	NodeName="Find Point In Circle";
	RoamRadius=3000;
}

EBTNodeResult::Type UBTT_FindPointAround::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ANPCBaseAIController* EnemyAIController=Cast<ANPCBaseAIController>(OwnerComp.GetAIOwner());
	// if (EnemyAIController->GetBlackboard()->GetValueAsObject(BlackboardKey.SelectedKeyName))
	// {
	// 	FinishLatentTask(OwnerComp,EBTNodeResult::Failed);
	// 	return EBTNodeResult::Failed;
	// }
	ACharacter* PossesedCharacter=EnemyAIController->GetCharacter();
	UNavigationSystemV1* NavSystem= UNavigationSystemV1::GetCurrent(GetWorld());
	if (NavSystem&&PossesedCharacter)
	{
		FNavLocation Location;
		NavSystem->GetRandomReachablePointInRadius(PossesedCharacter->GetActorLocation(),RoamRadius,Location);
		EnemyAIController->GetBlackboard()->SetValueAsVector(BlackboardKey.SelectedKeyName,Location);
		// EnemyAIController->MoveToLocation(Location);
		FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
		return EBTNodeResult::Succeeded;
	}
	FinishLatentTask(OwnerComp,EBTNodeResult::Failed);
	return EBTNodeResult::Failed;
}
