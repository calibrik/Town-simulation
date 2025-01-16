// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HealthBarWidget.h"

#include "Components/ProgressBar.h"

void UHealthBarWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UHealthBarWidget::SetHealthBarPercent(float Percent)
{
	HealthBar->SetPercent(Percent);
}
