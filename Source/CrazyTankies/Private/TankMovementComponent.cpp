// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "Tank.h"

UTankMovementComponent::UTankMovementComponent()
{
	PositionOffset = 0.0f;

	LeftTreadOffset = 0.0f;
	RightTreadOffset = 0.0f;

	LeftTreadDirection = 0;
	RightTreadDirection = 0;
}

void UTankMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	
	for (int i = 0; i < Wheels.Num(); i++)
	{
		DriveTorques.Add(0.0f);
		TotalWheelMass += Wheels[i]->Mass;	
	}

	ATank* Tank = Cast<ATank>(GetOwner());
	TArray<UTankTrack*> Tracks;
	Tank->GetComponents<UTankTrack>(Tracks);
	LeftTrack = Tracks[0];
	RightTrack = Tracks[1];
}

void UTankMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	for (int i = 0; i < Wheels.Num(); i++)
		SetDriveTorque(DriveTorques[i], i);

	LeftTrack->TreadSpeed = GetEngineRotationSpeed();
	RightTrack->TreadSpeed = GetEngineRotationSpeed();
}

void UTankMovementComponent::IntendDriveForward(float Torque)
{
	for (int i = 0; i < DriveTorques.Num(); i++)
	{
		DriveTorques[i] = Torque * Wheels[i]->Mass;
	}
}

void UTankMovementComponent::IntendSteerRight(float Torque)
{
	LeftTrack->TreadDirection = Torque;
	RightTrack->TreadDirection = -Torque;

	for (int i = 0; i < DriveTorques.Num(); i++)
	{
		if (i % 2 == 0)
			DriveTorques[i] += Torque * TotalWheelMass;
		else
			DriveTorques[i] -= Torque * TotalWheelMass;
	}
}

void UTankMovementComponent::IntendStop()
{
	for (int i = 0; i < Wheels.Num(); i++)
	{
		SetBrakeTorque(100000, i);
	}
}

void UTankMovementComponent::UndoStop()
{
	for (int i = 0; i < Wheels.Num(); i++)
	{
		SetBrakeTorque(0, i);
	}
}


void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{

}