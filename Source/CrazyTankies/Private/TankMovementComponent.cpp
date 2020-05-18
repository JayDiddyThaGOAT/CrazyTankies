// Fill out your copyright notice in the Description page of Project Settings.


#include "TankMovementComponent.h"
#include "Tank.h"

UTankMovementComponent::UTankMovementComponent()
{
	Mass = 5000.0f;
}

void UTankMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	
	for (int i = 0; i < Wheels.Num(); i++)
	{
		DriveTorques.Add(0.0f);
		TotalWheelMass += Wheels[i]->Mass;
	}

	ATank* Tank = Cast<ATank>(GetPawnOwner());
	TArray<UTankTrack*> Tracks;
	Tank->GetComponents<UTankTrack>(Tracks);
	LeftTrack = Tracks[0];
	RightTrack = Tracks[1];
}

void UTankMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	for (int i = 0; i < Wheels.Num(); i++)
	{
		SetDriveTorque(DriveTorques[i], i);
		SetBrakeTorque(BrakeTorque, i);
	}
	
	if (FMath::Abs(GetForwardSpeed()) < 0.3f)
	{
		if (!FMath::IsNearlyZero(BrakeTorque))
			return;

		if (!FMath::IsNearlyZero(RightTorque))
		{
			LeftTrack->TreadSpeed = 1.0f;
			RightTrack->TreadSpeed = 1.0f;
		}
		else
		{
			LeftTrack->TreadSpeed = 0.0f;
			RightTrack->TreadSpeed = 0.0f;
		}
	}
	else
	{
		LeftTrack->TreadSpeed = GetEngineRotationSpeed();
		RightTrack->TreadSpeed = GetEngineRotationSpeed();
	}

	if (FMath::IsNearlyZero(FMath::Abs(RightTorque), 0.5f))
	{
		LeftTrack->TreadDirection = !bFlipTreadDirection ? 1.0f : -1.0f;
		RightTrack->TreadDirection = !bFlipTreadDirection ? 1.0f : -1.0f;
	}
	else
	{
		LeftTrack->TreadDirection = !bFlipTreadDirection ? 1.0f : -1.0f;
		RightTrack->TreadDirection = !bFlipTreadDirection ? -1.0f : 1.0f;
	}
}

void UTankMovementComponent::IntendDriveForward(float Torque)
{
	ForwardTorque = Torque;

	for (int i = 0; i < DriveTorques.Num(); i++)
	{
		DriveTorques[i] = ForwardTorque * Wheels[i]->Mass;
	}
}

void UTankMovementComponent::IntendSteerRight(float Torque)
{
	RightTorque = Torque;

	for (int i = 0; i < DriveTorques.Num(); i++)
	{
		if (i % 2 == 0)
			DriveTorques[i] += RightTorque * TotalWheelMass;
		else
			DriveTorques[i] -= RightTorque * TotalWheelMass;
	}
}

void UTankMovementComponent::IntendStop()
{
	BrakeTorque = 100000.0f;
}

void UTankMovementComponent::UndoStop()
{
	BrakeTorque = 0.0f;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector AIForwardIntention = MoveVelocity.GetSafeNormal();

	ForwardTorque = FVector::DotProduct(TankForward, AIForwardIntention);
	RightTorque = FVector::CrossProduct(TankForward, AIForwardIntention).Z;

	UE_LOG(LogTemp, Warning, TEXT("%f"), RightTorque);

	IntendDriveForward(ForwardTorque);
	IntendSteerRight(RightTorque);
}