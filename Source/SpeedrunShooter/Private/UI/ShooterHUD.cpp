// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ShooterHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/HealthBarWidget.h"


void AShooterHUD::ShowCrosshair() const
{
	if (CrosshairWidget)
		CrosshairWidget->SetVisibility(ESlateVisibility::Visible);
}

void AShooterHUD::HideCrosshair() const
{
	if (CrosshairWidget)
		CrosshairWidget->SetVisibility(ESlateVisibility::Collapsed);
}

void AShooterHUD::SetHealthBarPercent(float Percent)
{
	HealthBarWidget->SetHealthBarPercent(Percent);
}

void AShooterHUD::BeginPlay()
{
	Super::BeginPlay();
	if (!CrosshairWidgetClass)
		return;
	CrosshairWidget=CreateWidget(GetWorld(),CrosshairWidgetClass);
	CrosshairWidget->AddToViewport(-2);
	ShowCrosshair();
	if (!HealthBarWidgetClass)
		return;
	HealthBarWidget=CreateWidget<UHealthBarWidget>(GetWorld(),HealthBarWidgetClass);
	HealthBarWidget->AddToViewport(-2);
	HealthBarWidget->SetVisibility(ESlateVisibility::Visible);
}

