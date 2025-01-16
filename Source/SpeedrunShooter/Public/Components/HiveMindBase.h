// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HiveMindBase.generated.h"

class ANPCBase;

UENUM()
enum EHiveMindState:uint8
{
	Vigilant UMETA(DisplayName="Vigilant"),
	Peaceful UMETA(DisplayName="Peaceful")
};
enum ENPCState : uint8;
DECLARE_MULTICAST_DELEGATE_OneParam(FOnChangeState, EHiveMindState)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPEEDRUNSHOOTER_API UHiveMindBase : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHiveMindBase();
	FOnChangeState OnChangeState;

	virtual void OnNPCDied();
	FORCEINLINE EHiveMindState GetState() const {return State;}
protected:
	UPROPERTY(EditInstanceOnly,Category="My Settings")
	TSubclassOf<ANPCBase> NPCClass;
	UPROPERTY(EditInstanceOnly,Category="My Settings")
	float MaxNPCAmount;
	EHiveMindState State;
	void SetState(EHiveMindState NewState);
	void SpawnNPCInPool();
};
