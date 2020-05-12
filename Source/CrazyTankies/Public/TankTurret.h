// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "TankBarrel.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Tank), meta = (BlueprintSpawnableComponent))
class CRAZYTANKIES_API UTankTurret : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:
    UTankTurret();

    float GetMinElevationDegrees() const;
    float GetMaxElevationDegrees() const;

    void Rotate(FRotator CurrentRotation, FRotator TargetRotation);
    void ElevateBarrel(FRotator CurrentRotation, FRotator TargetRotation);

private:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    float MaxDegreesPerSecond;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float MinElevationDegrees;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float MaxElevationDegrees;

protected:
    UPROPERTY(Category = Barrel, EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    class UTankBarrel* Barrel;
};
