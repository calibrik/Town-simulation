// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HiveMindBase.h"
#include "Components/ActorComponent.h"
#include "RangeEnemyHiveMind.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPEEDRUNSHOOTER_API URangeEnemyHiveMind : public UHiveMindBase
{
	GENERATED_BODY()

public:
	URangeEnemyHiveMind();
	static URangeEnemyHiveMind* S;
protected:
	FTimerHandle FindPlayerTimeoutHandle;
	UPROPERTY(EditInstanceOnly,Category="My Settings")
	float FindPlayerTimeout;
	float RangeEnemiesSeeingPlayerAmount;
	void StartFindPlayerTimer();
	virtual void BeginPlay() override;
public:
	// void ResetFindPlayerTimer();
	void OnPlayerSeen();
	virtual void OnNPCDied() override;
	void OnPlayerLost();
	virtual ~URangeEnemyHiveMind() override;
};
