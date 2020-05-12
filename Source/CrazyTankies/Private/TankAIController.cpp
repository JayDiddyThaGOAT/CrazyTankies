// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	
}
// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());

	if (!(PlayerTank && ControlledTank))
		return;
	
	Barrel = ControlledTank->FindComponentByClass<UTankBarrel>();
	AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	MovementComponent = ControlledTank->FindComponentByClass<UTankMovementComponent>();

	EPathFollowingRequestResult::Type FollowingPlayerRequest = MoveToActor(PlayerTank, AcceptanceRadius); // TODO check radius is in cm
	if (FollowingPlayerRequest == EPathFollowingRequestResult::AlreadyAtGoal || FollowingPlayerRequest == EPathFollowingRequestResult::Failed)
	{
		if (AimingComponent)
			MovementComponent->IntendStop();
		else
		{
			FHitResult HitResult;
			FVector StartLocation = Barrel->GetSocketLocation("Socket_Projectile");
			FVector EndLocation = StartLocation + (Barrel->GetForwardVector() * LineTraceRange);

			FCollisionQueryParams CollisionParams;
			CollisionParams.AddIgnoredActor(ControlledTank);

			if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility))
			{
				if (HitResult.Actor == PlayerTank)
					Barrel->FireProjectile();
			}
		}
	}
	else
	{
		if (AimingComponent)
			MovementComponent->UndoStop();
	}

	if (AimingComponent)
	{
		AimingComponent->AimAt(PlayerTank->GetActorLocation());

		if (AimingComponent->GetAimingState() == EAimingState::Locked)
			Barrel->FireProjectile();
	}
}