// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTT_Shoot.generated.h"

class AAIWeapon;
/**
 * 
 */
UCLASS()
class SPEEDRUNSHOOTER_API UBTT_Shoot : public UBTTaskNode
{
	GENERATED_BODY()
protected:
	UPROPERTY()
	UBehaviorTreeComponent* OwnerComponent;
	UPROPERTY(EditAnywhere)
	float ShootingDistance;
	UPROPERTY(EditAnywhere)
	float Damage;
	UPROPERTY()
	AAIWeapon* Weapon;
	UPROPERTY(EditAnywhere)
	FBlackboardKeySelector PlayerKey;
public:
	UBTT_Shoot();
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	UFUNCTION()
	void OnMontageEnded_Delegate();
};
