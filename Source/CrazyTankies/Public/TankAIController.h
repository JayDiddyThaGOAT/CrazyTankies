// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "Projectile.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class CRAZYTANKIES_API ATankAIController : public AAIController
{
	GENERATED_BODY()

protected:
	// How close can the AI tank get
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 500;

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UTankAimingComponent* AimingComponent;
	UTankMovementComponent* MovementComponent;
	UTankBarrel* Barrel;
};
