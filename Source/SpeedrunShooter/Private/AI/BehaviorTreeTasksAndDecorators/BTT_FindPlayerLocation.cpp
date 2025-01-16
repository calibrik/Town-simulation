// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviorTreeTasksAndDecorators/BTT_FindPlayerLocation.h"

#include "NavigationSystem.h"
#include "SpeedrunShooterPlayerController.h"
#include "AI/NPCBaseAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTT_FindPlayerLocation::UBTT_FindPlayerLocation(FObjectInitializer const& ObjectInit)
{
	NodeName=TEXT("Find Player Location");
}

EBTNodeResult::Type UBTT_FindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// AEnemyAIController* EnemyAIController=Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	// ASpeedrunShooterPlayerController* PlayerController=Cast<ASpeedrunShooterPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(),0));
	AActor* Player=Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(PlayerKey.SelectedKeyName));
	if (UNavigationSystemV1::GetCurrent(GetWorld()))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(BlackboardKey.SelectedKeyName,Player->GetActorLocation());
		// EnemyAIController->GetBlackBoard()->SetValueAsVector(TEXT("TargetLocation"),Player->GetActorLocation());
	}
	FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
