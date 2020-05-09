// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Projectile.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Tank), meta = (BlueprintSpawnableComponent))
class CRAZYTANKIES_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
    UTankBarrel();

	void FireProjectile();

	UPROPERTY(Category = Projectile, EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AProjectile> ProjectileBlueprint;

    UPROPERTY(Category = Projectile, EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float LaunchSpeed;
};
