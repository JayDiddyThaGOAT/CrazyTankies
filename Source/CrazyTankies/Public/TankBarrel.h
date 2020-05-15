// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Projectile.h"
#include "TankBarrel.generated.h"

UENUM()
enum class EFiringState : uint8
{
	Ready,
	Reloading
};

/**
 * Responsible for firing the projectiles
 */
UCLASS(ClassGroup = (Tank), meta = (BlueprintSpawnableComponent))
class CRAZYTANKIES_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
    UTankBarrel();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void FireProjectile();

	UPROPERTY(Category = Projectile, EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AProjectile> ProjectileBlueprint;

    UPROPERTY(Category = Projectile, EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float LaunchSpeed;

	UPROPERTY(Category = Projectile, EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float ReloadTimeInSeconds;

	EFiringState GetFiringState() const;

private:
	EFiringState FiringState;

	float LastTimeFired;
};
