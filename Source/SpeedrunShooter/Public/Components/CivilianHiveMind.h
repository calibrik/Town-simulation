// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HiveMindBase.h"
#include "Components/ActorComponent.h"
#include "CivilianHiveMind.generated.h"

class ACivilian;
enum ENPCState : uint8;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPEEDRUNSHOOTER_API UCivilianHiveMind : public UHiveMindBase
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCivilianHiveMind();
	static UCivilianHiveMind* S;
protected:
	FTimerHandle HidingTimerHandle;
	virtual void BeginPlay() override;
	UPROPERTY(EditInstanceOnly,Category="My Settings")
	float HidingTime;
	void StartHidingTimer();
	void ResetHidingTimer();
	virtual ~UCivilianHiveMind() override;
	
public:	
	void OnShoot();
};
