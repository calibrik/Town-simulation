// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VFXActor.generated.h"

class USphereComponent;

UCLASS()
class SPEEDRUNSHOOTER_API AVFXActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVFXActor();

protected:
	//if vfx is constant, set, otherwise leave on 0
	UPROPERTY(EditDefaultsOnly,Category="VFX")
	float LiveTime;
	UPROPERTY(EditDefaultsOnly,Category="VFX")
	UParticleSystemComponent* ParticleSystemComponent;
	UPROPERTY(EditDefaultsOnly,Category="Navigation")
	USphereComponent* SphereForNav;
	UPROPERTY(EditDefaultsOnly,Category="Navigation")
	bool bShouldAffectNavigation;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnParticleSystemFinished(UParticleSystemComponent* PSystem);
};
