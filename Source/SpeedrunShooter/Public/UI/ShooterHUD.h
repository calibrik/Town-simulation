// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
// #include "Blueprint/UserWidget.h"
#include "ShooterHUD.generated.h"
class UHealthBarWidget;
class UUserWidget;

/**
 * 
 */
UCLASS()
class SPEEDRUNSHOOTER_API AShooterHUD : public AHUD
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	UUserWidget* CrosshairWidget;
	UPROPERTY()
	UHealthBarWidget* HealthBarWidget;

	virtual void BeginPlay() override;
public:
	UPROPERTY(EditDefaultsOnly,Category="Shooting HUD")
	TSubclassOf<UUserWidget> CrosshairWidgetClass;
	UPROPERTY(EditDefaultsOnly,Category="Shooting HUD")
	TSubclassOf<UHealthBarWidget> HealthBarWidgetClass;
	void ShowCrosshair() const;
	void HideCrosshair() const;
	void SetHealthBarPercent(float Percent);
};
