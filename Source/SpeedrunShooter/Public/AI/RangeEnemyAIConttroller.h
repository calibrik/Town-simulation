// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/NPCBaseAIController.h"
#include "RangeEnemyAIConttroller.generated.h"


enum EHiveMindState : uint8;
class URangeEnemyHiveMind;
/**
 * 
 */
UCLASS()
class SPEEDRUNSHOOTER_API ARangeEnemyAIConttroller : public ANPCBaseAIController
{
	GENERATED_BODY()
protected:
	UPROPERTY()
	URangeEnemyHiveMind* HiveMind;
	UFUNCTION()
	void OnHiveMindStateChange_Delegate(EHiveMindState HiveMindState);
	virtual void BeginPlay() override;
public:
	ARangeEnemyAIConttroller();
	virtual void OnTargetPerceptionInfoUpdated_Delegate(const FActorPerceptionUpdateInfo& UpdateInfo) override;
	virtual void SetState(ENPCState NewState, bool bProcessPrevState=true) override;
	void SetShootingDistance(float Distance);
	// void SetHiveMind(URangeEnemyHiveMind* NewHiveMind);
};
