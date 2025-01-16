// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/NPCBase.h"
#include "Civilian.generated.h"

/**
 * 
 */
UCLASS()
class SPEEDRUNSHOOTER_API ACivilian : public ANPCBase
{
	GENERATED_BODY()

protected:
	// UPROPERTY(EditInstanceOnly,Category="My Settings|Hive Mind")
	// AActor* ActorWithHiveMindComponent;
	virtual void UnFreeze(UAnimMontage* Montage, bool bInterrupted) override;
	virtual void Freeze() override;
	virtual void BeginPlay() override;
	virtual void Die() override;
};
