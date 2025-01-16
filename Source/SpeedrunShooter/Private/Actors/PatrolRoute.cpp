// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/PatrolRoute.h"

#include "Components/SplineComponent.h"

// Sets default values
APatrolRoute::APatrolRoute()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SplineComponent=CreateDefaultSubobject<USplineComponent>(TEXT("Patrol Route"));
	SplineComponent->SetTangentColor(FLinearColor(0,1,0));
	SplineComponent->SetUnselectedSplineSegmentColor(FLinearColor(0,1,0));
	SplineComponent->SetClosedLoop(true);
	SetRootComponent(SplineComponent);
}

// Called when the game starts or when spawned
void APatrolRoute::BeginPlay()
{
	Super::BeginPlay();
}

FVector APatrolRoute::GetPointWorldPosition(uint8 Index) const
{
	UE_LOG(LogTemp,Log,TEXT("%d"),Index);
	return SplineComponent->GetLocationAtSplinePoint(Index,ESplineCoordinateSpace::World);
}

void APatrolRoute::GetAllPointsWorldPosition(TArray<FVector>& Out) const
{
	uint8 Total=GetTotal();
	for (int i=0;i<Total;i++)
		Out.Add(SplineComponent->GetLocationAtSplinePoint(i,ESplineCoordinateSpace::World));
}

uint8 APatrolRoute::GetTotal() const
{
	return SplineComponent->GetNumberOfSplinePoints();
}

