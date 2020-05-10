// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "TankMovementComponent.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}
// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = Cast<ATank>(GetPawn());

	if (!(PlayerTank && ControlledTank))
		return;

	
	EPathFollowingRequestResult::Type FollowingPlayerRequest = MoveToActor(PlayerTank, AcceptanceRadius); // TODO check radius is in cm
	if (FollowingPlayerRequest == EPathFollowingRequestResult::AlreadyAtGoal || FollowingPlayerRequest == EPathFollowingRequestResult::Failed)
		ControlledTank->FindComponentByClass<UTankMovementComponent>()->IntendStop();
	else
		ControlledTank->FindComponentByClass<UTankMovementComponent>()->UndoStop();
}