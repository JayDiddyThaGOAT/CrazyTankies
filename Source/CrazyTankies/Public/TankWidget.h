// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "TankWidget.generated.h"

/**
 * 
 */
UCLASS()
class CRAZYTANKIES_API UTankWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetCrosshairColor(FLinearColor Color);
	void SetHullAngle(float Angle);
	void SetTurretAngle(float Angle);

private:
	UPROPERTY(meta = (BindWidget))
	class UImage* Crosshair;

	UPROPERTY(meta = (BindWidget))
	class UImage* Hull;

	UPROPERTY(meta = (BindWidget))
	class UImage* Turret;
};
