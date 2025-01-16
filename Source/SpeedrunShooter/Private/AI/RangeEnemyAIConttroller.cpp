// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/RangeEnemyAIConttroller.h"

#include "SpeedrunShooterCharacter.h"
#include "Actors/PatrolRoute.h"
#include "AI/NPCBase.h"
#include "AI/RangeEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/RangeEnemyHiveMind.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Prediction.h"

void ARangeEnemyAIConttroller::OnHiveMindStateChange_Delegate(EHiveMindState HiveMindState)
{
	switch (HiveMindState)
	{
		case Vigilant:
			break;
		case Peaceful:
			{
				if (GetState()==Aggressive)
					SetState(Investigating);
			}
			break;
	}
}

void ARangeEnemyAIConttroller::BeginPlay()
{
	Super::BeginPlay();
	HiveMind=URangeEnemyHiveMind::S;
	HiveMind->OnChangeState.AddUObject(this,&ARangeEnemyAIConttroller::OnHiveMindStateChange_Delegate);
	GetBlackboard()->SetValueAsObject(TEXT("Player"),UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
}

ARangeEnemyAIConttroller::ARangeEnemyAIConttroller()
{
	
}

void ARangeEnemyAIConttroller::OnTargetPerceptionInfoUpdated_Delegate(const FActorPerceptionUpdateInfo& UpdateInfo)
{
	if (GetState()==Frozen) return;
	
	if (!UpdateInfo.Stimulus.WasSuccessfullySensed())
	{
		if (UpdateInfo.Stimulus.Type.Name=="Default__AISense_Sight")
		{
			if (Cast<ASpeedrunShooterCharacter>(UpdateInfo.Target))
			{
				if (GetState()==Aggressive)
					HiveMind->OnPlayerLost();
			}
			return;
		}
		UE_LOG(LogTemp,Log,TEXT("Unhandled sense ended %s"),*UpdateInfo.Stimulus.Type.Name.ToString())
	}
	else
	{
		if (UpdateInfo.Stimulus.Type.Name=="Default__AISense_Sight")
		{
			if (ASpeedrunShooterCharacter* Player=Cast<ASpeedrunShooterCharacter>(UpdateInfo.Target))
			{
				if (Player->GetHasRifle()||HiveMind->GetState()==Vigilant)
				{
					HiveMind->OnPlayerSeen();
					// GetBlackboard()->SetValueAsObject(TEXT("Player"),Player);
					SetState(Aggressive);
					UE_LOG(LogTemp,Log,TEXT("Found Player"));
				}
			}
			if (Cast<ARangeEnemy>(UpdateInfo.Target)&&GetState()==Investigating&&HiveMind->GetState()==Vigilant)
			{
				SetState(Aggressive);
			}
			return;
		}
		if (UpdateInfo.Stimulus.Type.Name=="Default__AISense_Hearing")
		{
			if (GetState()==Aggressive)
				return;
			SetState(Investigating);
			GetBlackboard()->SetValueAsVector(TEXT("LastKnownPlayerLocation"),UpdateInfo.Stimulus.StimulusLocation);
			UE_LOG(LogTemp,Log,TEXT("Heard Player"));
			
		}
		if (UpdateInfo.Stimulus.Type.Name=="Default__AISense_Prediction")
		{
			if (Cast<ASpeedrunShooterCharacter>(UpdateInfo.Target))
			{
				FVector PredictionLocation{FVector(UpdateInfo.Stimulus.StimulusLocation.X,UpdateInfo.Stimulus.StimulusLocation.Y,0)};
				GetBlackboard()->SetValueAsVector(TEXT("LastKnownPlayerLocation"),PredictionLocation);
			}
		}
		UE_LOG(LogTemp,Log,TEXT("Unhandled sense commenced %s"),*UpdateInfo.Stimulus.Type.Name.ToString())
	}
	
	
}

void ARangeEnemyAIConttroller::SetState(ENPCState NewState, bool bProcessPrevState)
{
	ENPCState PrevState=GetState();
	if (NewState==PrevState) return;
	
	if (bProcessPrevState)
	{
		switch (PrevState)
		{
			case Aggressive:
				{
					UE_LOG(LogTemp,Log,TEXT("Aggressive no more"));
					ClearFocus(EAIFocusPriority::Gameplay);
					if (NewState==Investigating)
					{
						UAISense_Prediction::RequestPawnPredictionEvent(GetPawn(),UGameplayStatics::GetPlayerCharacter(GetWorld(),0),1);
					}
				}
				break;
			case Investigating:
				UE_LOG(LogTemp,Log,TEXT("Investigating no more"));
				GetBlackboard()->ClearValue("LastKnownPlayerLocation");
				break;
			case Hiding:
				UE_LOG(LogTemp,Log,TEXT("Hiding no more"));
				break;
			case Patroling:
				UE_LOG(LogTemp,Log,TEXT("Patroling no more"));
				break;
			case Frozen:
				{
					ACharacter* Player=UGameplayStatics::GetPlayerCharacter(GetWorld(),0);
					GetBlackboard()->SetValueAsObject(TEXT("Player"),Player);
				}
				break;
		}
	}
	switch (NewState)
	{
		case Aggressive:
			{
				UE_LOG(LogTemp,Log,TEXT("Aggressive"));
				ACharacter* Player=UGameplayStatics::GetPlayerCharacter(GetWorld(),0);
				SetFocus(Player);
				ARangeEnemy* PossessedPawn=Cast<ARangeEnemy>(GetPawn());
				PossessedPawn->GetCharacterMovement()->MaxWalkSpeed=RunningSpeed;
			}
			break;
		case Investigating:
			{
				UE_LOG(LogTemp,Log,TEXT("Investigating"));
				ARangeEnemy* PossessedPawn=Cast<ARangeEnemy>(GetPawn());
				PossessedPawn->GetCharacterMovement()->MaxWalkSpeed=RunningSpeed;
			}
			break;
		case Hiding:
			UE_LOG(LogTemp,Log,TEXT("Hiding"));
			break;
		case Patroling:
			{
				UE_LOG(LogTemp,Log,TEXT("Patroling"));
				ARangeEnemy* PossessedPawn=Cast<ARangeEnemy>(GetPawn());
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
			StopMovement();
			break;
	}
	State=NewState;
	GetBlackboard()->SetValueAsEnum("State",NewState);
}

void ARangeEnemyAIConttroller::SetShootingDistance(float Distance)
{
	GetBlackboard()->SetValueAsFloat("ShootingDistance",Distance);
}

