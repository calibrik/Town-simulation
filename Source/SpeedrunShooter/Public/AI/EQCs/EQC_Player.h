// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "EQC_Player.generated.h"

/**
 * 
 */
UCLASS()
class SPEEDRUNSHOOTER_API UEQC_Player : public UEnvQueryContext
{
	GENERATED_BODY()
public:
	UEQC_Player();
	virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;
};
