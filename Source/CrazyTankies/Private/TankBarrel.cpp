// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

UTankBarrel::UTankBarrel()
{
	LaunchSpeed = 5000.0f;
	SetCollisionProfileName(TEXT("BlockAll"));
}

void UTankBarrel::FireProjectile()
{
	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileBlueprint,
		GetSocketTransform(TEXT("Socket_Projectile"))
	);

	Projectile->Launch(LaunchSpeed);
}
