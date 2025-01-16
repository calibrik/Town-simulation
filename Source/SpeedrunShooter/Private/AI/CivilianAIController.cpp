// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/CivilianAIController.h"

#include "SpeedrunShooterCharacter.h"
#include "Actors/PatrolRoute.h"
#include "AI/Civilian.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CivilianHiveMind.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"

void ACivilianAIController::OnHiveMindChangeState_Delegate(EHiveMindState HiveMindState)
{
	switch (HiveMindState)
	{
		case Vigilant:
			break;
		case Peaceful:
			{
				SetState(Patroling);
			}
			break;
	}
}

void ACivilianAIController::BeginPlay()
{
	Super::BeginPlay();
	HiveMind=UCivilianHiveMind::S;
	HiveMind->OnChangeState.AddUObject(this,&ACivilianAIController::OnHiveMindChangeState_Delegate);
	GetBlackboard()->SetValueAsObject(TEXT("Player"),UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
}

void ACivilianAIController::OnTargetPerceptionInfoUpdated_Delegate(const FActorPerceptionUpdateInfo& UpdateInfo)
{
	if (GetState()==Frozen) return;
	
	if (!UpdateInfo.Stimulus.WasSuccessfullySensed())
	{
		if (UpdateInfo.Stimulus.Type.Name=="Default__AISense_Sight")
		{
			// if (ASpeedrunShooterCharacter* Player=Cast<ASpeedrunShooterCharacter>(UpdateInfo.Target))
			// {
			// 	GetBlackboard()->ClearValue(TEXT("Player"));
			// }
			return;
		}
		UE_LOG(LogTemp,Log,TEXT("Unhandled sense %s"),*UpdateInfo.Stimulus.Type.Name.ToString())
	}
	else
	{
		if (UpdateInfo.Stimulus.Type.Name=="Default__AISense_Sight")
		{
			if (ASpeedrunShooterCharacter* Player= Cast<ASpeedrunShooterCharacter>(UpdateInfo.Target))
			{
				if (HiveMind->GetState()==Vigilant&&Player->GetHasRifle())
					SetState(Hiding);
			}
			if (ACivilian* Civilian=Cast<ACivilian>(UpdateInfo.Target))
			{
				if (Civilian->GetControllerState()==Hiding)
					SetState(Hiding);
			}
			return;
		}
		if (UpdateInfo.Stimulus.Type.Name=="Default__AISense_Hearing")
		{
			OnPlayerShoot();
			SetState(Hiding);
		}
		UE_LOG(LogTemp,Log,TEXT("Unhandled sense %s"),*UpdateInfo.Stimulus.Type.Name.ToString())
	}
}

void ACivilianAIController::SetState(ENPCState NewState, bool bProcessPrevState)
{
	ENPCState PrevState=GetState();
	if (NewState==PrevState) return;
	
	if (bProcessPrevState)
	{
		switch (PrevState)
		{
		case Hiding:
			UE_LOG(LogTemp,Log,TEXT("Hiding no more"));
			break;
		case Patroling:
			UE_LOG(LogTemp,Log,TEXT("Patroling no more"));
			break;
		case Frozen:
			break;
		case Aggressive:
			break;
		case Investigating:
			break;
		}
	}
	switch (NewState)
	{
	case Hiding:
		{
			UE_LOG(LogTemp,Log,TEXT("Hiding"));
			ACivilian* PossessedPawn=Cast<ACivilian>(GetPawn());
			PossessedPawn->GetCharacterMovement()->MaxWalkSpeed=RunningSpeed;
		}
		break;
	case Patroling:
		{
			UE_LOG(LogTemp,Log,TEXT("Patroling"));
			ACivilian* PossessedPawn=Cast<ACivilian>(GetPawn());
			PossessedPawn->GetCharacterMovement()->MaxWalkSpeed=WalkingSpeed;
			APatrolRoute* PatrolRoute=PossessedPawn->GetPatrolRoute();
			if (!PatrolRoute)
				break;
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
			PossessedPawn->SetPatrolRouteIndex(CurrMinIndex);
		}
		break;
	case Frozen:
		break;
	case Aggressive:
		break;
	case Investigating:
		break;
	}
	State=NewState;
	GetBlackboard()->SetValueAsEnum("State",NewState);
}

void ACivilianAIController::OnPlayerShoot()
{
	HiveMind->OnShoot();
}
//
// void ACivilianAIController::SetHiveMind(UCivilianHiveMind* NewHiveMind)
// {
// 	HiveMind=NewHiveMind;
// 	HiveMind->OnChangeState.AddUObject(this,&ACivilianAIController::OnHiveMindChangeState_Delegate);
// }

