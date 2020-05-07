// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "Tank.h"

ATankPlayerController::ATankPlayerController()
{

}

// Called when the game starts or when spawned
void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(AcknowledgedPawn);
}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATankPlayerController::SetupInputComponent()
{
	if (InputComponent == nullptr)
	{
		InputComponent = NewObject<UInputComponent>(this, TEXT("PC_InputComponent0"));
		InputComponent->RegisterComponent();
	}

	InputComponent->BindAxis(TEXT("AimHorizontal"), this, &ATankPlayerController::AimHorizontally);
	InputComponent->BindAxis(TEXT("AimVertical"), this, &ATankPlayerController::AimVertically);
}

void ATankPlayerController::AimHorizontally(float Val)
{
	Tank->SpringArm->AddWorldRotation(FRotator(0.0f, Val, 0.0f));
}

void ATankPlayerController::AimVertically(float Val)
{
	Tank->SpringArm->AddLocalRotation(FRotator(Val, 0.0f, 0.0f));
}
