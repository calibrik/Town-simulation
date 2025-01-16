// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBarWidget.generated.h"

class UProgressBar;
/**
 * 
 */
UCLASS()
class SPEEDRUNSHOOTER_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta=(BindWidget))
	UProgressBar* HealthBar;
	virtual void NativeOnInitialized() override;
public:
	void SetHealthBarPercent(float Percent);
};
