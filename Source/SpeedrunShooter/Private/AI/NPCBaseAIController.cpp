// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/NPCBaseAIController.h"


#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISense_Prediction.h"
#include "Perception/AISense_Sight.h"


ANPCBaseAIController::ANPCBaseAIController()
{
	// static ConstructorHelpers::FObjectFinder<UBehaviorTree> treeFinder(TEXT(""))
	TreeComponent=CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior Tree Component"));
	AIPerceptionComponent=CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception Component"));
	// AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this,&AEnemyAIController::OnTargetPerceptionUpdated_Delegate);
	// AIPerceptionComponent->OnTargetPerceptionForgotten.AddDynamic(this,&AEnemyAIController::OnTargetPerceptionForgotten_Delegate);
	AIPerceptionComponent->OnTargetPerceptionInfoUpdated.AddDynamic(this,&ANPCBaseAIController::OnTargetPerceptionInfoUpdated_Delegate);
	WalkingSpeed=150;
	RunningSpeed=400;
}

void ANPCBaseAIController::BeginPlay()
{
	Super::BeginPlay();
	// UAISystem::GetCurrent(*GetWorld())->bForgetStaleActors=true;
	if (!Tree)
		return;
	RunBehaviorTree(Tree);
	TreeComponent->StartTree(*Tree);
}

void ANPCBaseAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	// GetBlackboard()->SetValueAsInt(TEXT("CurrIndex"),-1);
}
void ANPCBaseAIController::SetState(ENPCState NewState,bool bProcessPrevState)
{
	ENPCState PrevState=GetState();
	
	if (bProcessPrevState)
	{
		if (NewState==PrevState) return;
		
		switch (PrevState)
		{
		case Aggressive:
			break;
		case Investigating:
			break;
		case Hiding:
			break;
		case Patroling:
			break;
		case Frozen:
			break;
		}
	}
	switch (NewState)
	{
	case Aggressive:
		break;
	case Investigating:
		break;
	case Hiding:
		break;
	case Patroling:
		break;
	case Frozen:
		break;
	}
	State=NewState;
	GetBlackboard()->SetValueAsEnum("State",NewState);
}

ENPCState ANPCBaseAIController::GetState() const
{
	// return static_cast<ENPCState>(GetBlackboard()->GetValueAsEnum("State"));
	return State;
}

void ANPCBaseAIController::StopAI()
{
	TreeComponent->StopTree();
	AIPerceptionComponent->SetSenseEnabled(UAISense_Sight::StaticClass(),false);
	AIPerceptionComponent->SetSenseEnabled(UAISense_Hearing::StaticClass(),false);
}

void ANPCBaseAIController::StartAI()
{
	RunBehaviorTree(Tree);
	TreeComponent->StartTree(*Tree);
	AIPerceptionComponent->SetSenseEnabled(UAISense_Sight::StaticClass(),true);
	AIPerceptionComponent->SetSenseEnabled(UAISense_Hearing::StaticClass(),true);
}

void ANPCBaseAIController::OnTargetPerceptionInfoUpdated_Delegate(const FActorPerceptionUpdateInfo& UpdateInfo)
{
	if (GetState()==Frozen) return;
	
	if (!UpdateInfo.Stimulus.WasSuccessfullySensed())
	{
		if (UpdateInfo.Stimulus.Type.Name=="Default__AISense_Sight")
			return;
	}
	else
	{
		if (UpdateInfo.Stimulus.Type.Name=="Default__AISense_Sight")
			return;
	}
}
// void AEnemyAIController::OnTargetPerceptionUpdated_Delegate(AActor* Actor, FAIStimulus Stimulus)
// {
// 	switch (Stimulus.Type)
// 	{
// 	case 0:
// 		if (ASpeedrunShooterCharacter* Player=Cast<ASpeedrunShooterCharacter>(Actor))
// 		{
// 			GetBlackboard()->SetValueAsObject(TEXT("Player"),Player);
// 			UE_LOG(LogTemp,Log,TEXT("Found Player"));
// 		}
// 		break;
// 	default:
// 		UE_LOG(LogTemp,Log,TEXT("Unhandled sensor"));
// 	}
// }
//
// void AEnemyAIController::OnTargetPerceptionForgotten_Delegate(AActor* Actor)
// {
// 	UE_LOG(LogTemp,Log,TEXT("Forgot Player"));
// 	if (GetBlackboard()->GetValueAsObject(TEXT("Player")))
// 		UE_LOG(LogTemp,Log,TEXT("Lost Player"));
// 	GetBlackboard()->SetValueAsObject(TEXT("Player"),nullptr);
// }





