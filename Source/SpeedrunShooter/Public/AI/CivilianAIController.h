// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/NPCBaseAIController.h"
#include "CivilianAIController.generated.h"

enum EHiveMindState : uint8;
class UCivilianHiveMind;
/**
 * 
 */
UCLASS()
class SPEEDRUNSHOOTER_API ACivilianAIController : public ANPCBaseAIController
{
	GENERATED_BODY()
protected:
	UPROPERTY()
	UCivilianHiveMind* HiveMind;
	UFUNCTION()
	void OnHiveMindChangeState_Delegate(EHiveMindState HiveMindState);
	virtual void BeginPlay() override;
public:
	virtual void OnTargetPerceptionInfoUpdated_Delegate(const FActorPerceptionUpdateInfo& UpdateInfo) override;
	virtual void SetState(ENPCState NewState, bool bProcessPrevState=true) override;
	void OnPlayerShoot();
};
