// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

UTankTurret::UTankTurret()
{
	SetSimulatePhysics(false);
	SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	Barrel = CreateDefaultSubobject<UTankBarrel>(TEXT("Barrel"));
	Barrel->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform, TEXT("Socket_Barrel"));
	Barrel->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
}