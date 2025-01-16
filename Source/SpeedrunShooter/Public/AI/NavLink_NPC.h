// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Navigation/NavLinkProxy.h"
#include "NavLink_NPC.generated.h"

/**
 * 
 */
UCLASS()
class SPEEDRUNSHOOTER_API ANavLink_NPC : public ANavLinkProxy
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnSmartLinkReached_Delegate(AActor* MovingActor, const FVector& DestinationPoint);
};
