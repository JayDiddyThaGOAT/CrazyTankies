// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"
#include "Tank.h"

UTankBarrel::UTankBarrel()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<AProjectile> DefaultProjectileFinder(TEXT("/Game/Tanks/Projectile/BP_Wep_Tank_Projectile"));
	ProjectileBlueprint = DefaultProjectileFinder.Class;

	LaunchSpeed = 5000.0f;
	ReloadTimeInSeconds = 3.0f;
	SetCollisionProfileName(TEXT("BlockAll"));

	LastTimeFired = FPlatformTime::Seconds();
}

void UTankBarrel::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (FPlatformTime::Seconds() - LastTimeFired < ReloadTimeInSeconds)
		FiringState = EFiringState::Reloading;
	else
		FiringState = EFiringState::Ready;
}

void UTankBarrel::FireProjectile()
{
	if (FiringState == EFiringState::Ready)
	{
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			GetSocketTransform(TEXT("Socket_Projectile"))
			);
		Projectile->Launch(LaunchSpeed);

		LastTimeFired = FPlatformTime::Seconds();
	}
}

EFiringState UTankBarrel::GetFiringState() const
{
	return FiringState;
}