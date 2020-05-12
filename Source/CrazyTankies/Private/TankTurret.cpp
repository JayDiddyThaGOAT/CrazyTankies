// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"
#include "Kismet/KismetMathLibrary.h"

UTankTurret::UTankTurret()
{
	SetSimulatePhysics(false);
	SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	Barrel = CreateDefaultSubobject<UTankBarrel>(TEXT("Barrel"));
	Barrel->SetupAttachment(this, TEXT("Socket_Barrel"));
	Barrel->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	MaxDegreesPerSecond = 1.0f;
	MinElevationDegrees = -11.0f;
	MaxElevationDegrees = 10.0f;
}


float UTankTurret::GetMinElevationDegrees() const
{
	return MinElevationDegrees;
}

float UTankTurret::GetMaxElevationDegrees() const
{
	return MaxElevationDegrees;
}

void UTankTurret::Rotate(FRotator CurrentRotation, FRotator TargetRotation)
{
	FRotator InterpRotation = UKismetMathLibrary::RInterpTo(CurrentRotation, TargetRotation, GetWorld()->GetDeltaSeconds(), MaxDegreesPerSecond);
	SetWorldRotation(FRotator(0.0f, InterpRotation.Yaw, 0.0f));
}

void UTankTurret::ElevateBarrel(FRotator CurrentRotation, FRotator TargetRotation)
{
	FRotator InterpRotation = UKismetMathLibrary::RInterpTo(CurrentRotation, TargetRotation, GetWorld()->GetDeltaSeconds(), MaxDegreesPerSecond);

	InterpRotation.Pitch = UKismetMathLibrary::ClampAngle(InterpRotation.Pitch, MinElevationDegrees, MaxElevationDegrees);
	Barrel->SetRelativeRotation(FRotator(InterpRotation.Pitch, 0.0f, 0.0f));
}