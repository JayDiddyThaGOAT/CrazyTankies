// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

UTankBarrel::UTankBarrel()
{
	LaunchSpeed = 5000.0f;
}

void UTankBarrel::FireProjectile()
{
	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileBlueprint,
		GetSocketLocation(TEXT("Socket_Projectile")),
		GetSocketRotation(TEXT("Socket_Projectile"))
	);

	Projectile->Launch(LaunchSpeed);
}
