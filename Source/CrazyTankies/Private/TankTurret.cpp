// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

UTankTurret::UTankTurret()
{
	SetSimulatePhysics(false);
	SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	Barrel = CreateDefaultSubobject<UTankBarrel>(TEXT("Barrel"));
	Barrel->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform, TEXT("Socket_Barrel"));
	Barrel->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	MaxDegreesPerSecond = 3.0f;
	MinElevationDegrees = 0.0f;
	MaxElevationDegrees = 10.0f;
}

void UTankTurret::RotateTurret(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	AddRelativeRotation(FRotator(0, RelativeSpeed / MaxDegreesPerSecond, 0));
}

void UTankTurret::ElevateBarrel(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	Barrel->AddRelativeRotation(FRotator(RelativeSpeed / MaxDegreesPerSecond, 0.0f, 0.0f));
}