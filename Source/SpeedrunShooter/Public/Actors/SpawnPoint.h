// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnPoint.generated.h"

class ASpeedrunShooterCharacter;
class APatrolRoute;
class ANPCBase;

UCLASS()
class SPEEDRUNSHOOTER_API ASpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnPoint();
	static TQueue<ANPCBase*> SpawnQueue;
protected:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Mesh;
	FTimerHandle SpawnHandle;
	UPROPERTY(EditDefaultsOnly, Category="My Settings")
	float SpawnRate;
	UPROPERTY(EditAnywhere, Category="My Settings|Route")
	APatrolRoute* PatrolRoute;
	UPROPERTY(EditAnywhere, Category="My Settings|Route")
	bool bPatrolRouteDirection;
	UPROPERTY()
	ASpeedrunShooterCharacter* Player;
	
	void SpawnNPC();
	virtual void BeginPlay() override;
	virtual ~ASpawnPoint() override;
};
