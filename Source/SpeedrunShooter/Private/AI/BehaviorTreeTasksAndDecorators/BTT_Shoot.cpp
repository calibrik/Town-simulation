// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BehaviorTreeTasksAndDecorators/BTT_Shoot.h"

#include "AIController.h"
#include "AI/RangeEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Weapon/AIWeapon.h"

UBTT_Shoot::UBTT_Shoot()
{
	bCreateNodeInstance=true;
	NodeName="Shoot";
}

EBTNodeResult::Type UBTT_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ARangeEnemy* NPC=Cast<ARangeEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	Weapon=NPC->GetWeapon();
	OwnerComponent=&OwnerComp;
	Weapon->OnAnimEnded.BindUObject(this,&UBTT_Shoot::OnMontageEnded_Delegate);
	AActor* Player = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(PlayerKey.SelectedKeyName));
	Weapon->StartFire(Player);
	
	return EBTNodeResult::InProgress;
}

void UBTT_Shoot::OnMontageEnded_Delegate()
{
	Weapon->OnAnimEnded.Unbind();
	FinishLatentTask(*OwnerComponent,EBTNodeResult::Succeeded);
}

