// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimpleWheeledVehicleMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TankMovementComponent.generated.h"

/**
 * Responsible for driving the tanks
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class CRAZYTANKIES_API UTankMovementComponent : public USimpleWheeledVehicleMovementComponent
{
	GENERATED_BODY()

public:
	UTankMovementComponent();

	void IntendDriveForward(float Torque);
	void IntendSteerRight(float Torque);
	void IntendStop();
	void UndoStop();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
private:
	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

	class UStaticMeshComponent* LeftTrack;
	class UStaticMeshComponent* RightTrack;

	class UMaterialInstanceDynamic* LeftTread;
	class UMaterialInstanceDynamic* RightTread;

	float TotalWheelMass;
	TArray<float> DriveTorques;

	float LeftTreadUVOffset, RightTreadUVOffset;
	float LeftTreadOffset, RightTreadOffset;
	float LeftTrackLength, RightTrackLength;
	int32 LeftTreadDirection, RightTreadDirection;

	float PositionOffset;
};
