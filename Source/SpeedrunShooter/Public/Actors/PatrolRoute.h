// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PatrolRoute.generated.h"

class USplineComponent;

UCLASS()
class SPEEDRUNSHOOTER_API APatrolRoute : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APatrolRoute();

protected:
	UPROPERTY()
	USplineComponent* SplineComponent;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:

	
	
	UFUNCTION(BlueprintPure,Category="Patrol Route")
	FVector GetPointWorldPosition(uint8 Index) const;
	
	void GetAllPointsWorldPosition(TArray<FVector>& Out) const;
	uint8 GetTotal() const;
};
