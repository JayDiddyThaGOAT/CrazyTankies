// Fill out your copyright notice in the Description page of Project Settings.


#include "TankWidget.h"

void UTankWidget::SetCrosshairColor(FLinearColor Color)
{
	Crosshair->SetColorAndOpacity(Color);
}

void UTankWidget::SetHullAngle(float Angle)
{
	Hull->SetRenderTransformAngle(Angle);
}

void UTankWidget::SetTurretAngle(float Angle)
{
	Turret->SetRenderTransformAngle(Angle);
}
