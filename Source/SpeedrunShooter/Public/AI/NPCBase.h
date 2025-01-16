// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPCBaseAIController.h"
#include "GameFramework/Character.h"
#include "NPCBase.generated.h"

enum ENPCState : uint8;
class ANPCBaseAIController;
class UWidgetComponent;
class UHealthBarWidget;
class APatrolRoute;
class UAIBehaviorComponent;

UCLASS()
class SPEEDRUNSHOOTER_API ANPCBase : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditInstanceOnly,Category="My Settings|Patrol Route")
	APatrolRoute* PatrolRoute;
	UPROPERTY(VisibleInstanceOnly,Category="My Settings|Patrol Route")
	int PatrolRouteIndex;
	UPROPERTY(EditAnywhere,Category="My Settings|Patrol Route")
	bool PatrolRouteDirection;
	UPROPERTY(EditAnywhere,Category="My Settings|Health")
	float MaxHealth;
	UPROPERTY(VisibleAnywhere,Category="My Settings|Health")
	float Health;
	UPROPERTY(EditDefaultsOnly)
	UWidgetComponent* HealthBarComponent;
	UPROPERTY()
	UHealthBarWidget* HealthBarWidget;
	// UPROPERTY()
	// ACharacter* Player;
	UPROPERTY(EditDefaultsOnly,Category="Anims")
	UAnimMontage* HitAnim;
	UPROPERTY()
	ANPCBaseAIController* AIController;
	FTimerHandle HealthBarVisionHandle;
	bool bIsHealthBarVisible;
	UPROPERTY()
	ASpeedrunShooterCharacter* Player;
	UPROPERTY()
	UAnimInstance* AnimInstance;
	
	UFUNCTION()
	virtual void UnFreeze(UAnimMontage* Montage, bool bInterrupted);
	UFUNCTION()
	void ToggleHealthBar();
	virtual void Freeze();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	ANPCBase();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Damage(float Damage);
	virtual void Die();
	UFUNCTION(BlueprintCallable,Category="Patrol Route")
	void IncrementPatrolRouteIndex();
	void JumpTo(FVector Dest);
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	UFUNCTION(BlueprintCallable,Category="Patrol Route")
	FORCEINLINE APatrolRoute* GetPatrolRoute() const {return PatrolRoute;}
	FORCEINLINE void SetPatrolRoute(APatrolRoute* NewRoute) {PatrolRoute=NewRoute;}
	FORCEINLINE void SetPatrolRouteDirection(bool bNewDirection) {PatrolRouteDirection=bNewDirection;}
	FORCEINLINE bool IsAlive() const {return Health>0;}
	UFUNCTION(BlueprintCallable,Category="Patrol Route")
	FORCEINLINE int GetPatrolRouteIndex() const {return PatrolRouteIndex;}
	FORCEINLINE void SetPatrolRouteIndex(int NewIndex) {PatrolRouteIndex=NewIndex;}
	FORCEINLINE ENPCState GetControllerState() const {return AIController->GetState();}
	FORCEINLINE void SetControllerState(ENPCState NewState,bool bProcessPrevState=true) const {AIController->SetState(NewState,bProcessPrevState);}
	FORCEINLINE void StartAIController() const {AIController->StartAI();}
	FORCEINLINE void StopAIController() const {AIController->StopAI();}
};
