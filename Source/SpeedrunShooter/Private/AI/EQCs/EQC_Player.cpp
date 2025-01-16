// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EQCs/EQC_Player.h"

#include "SpeedrunShooterCharacter.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Point.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

UEQC_Player::UEQC_Player()
{
}

void UEQC_Player::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	// Super::ProvideContext(QueryInstance, ContextData);
	// UEnvQueryContext_BlueprintBase
	// AActor* Player=UGameplayStatics::GetActorOfClass(GetWorld(),APlayerStart::StaticClass());
	AActor* Player=Cast<AActor>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	UEnvQueryItemType_Actor::SetContextHelper(ContextData, Player);
}
