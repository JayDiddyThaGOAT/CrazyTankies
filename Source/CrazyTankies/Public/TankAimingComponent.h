// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankTurret.h"
#include "TankBarrel.h"
#include "TankAimingComponent.generated.h"


UCLASS( ClassGroup=(Tank), meta=(BlueprintSpawnableComponent) )
class CRAZYTANKIES_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AimAt(FVector HitLocation);

private:
	void MoveBarrelTowards(FVector AimDirection);

	class UTankTurret* Turret;
	class UTankBarrel* Barrel;
};
