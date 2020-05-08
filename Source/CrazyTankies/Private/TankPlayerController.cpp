// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "Tank.h"

ATankPlayerController::ATankPlayerController()
{
	ConstructorHelpers::FClassFinder<UTankWidget> TankUIFinder(TEXT("/Game/Tanks/UI/WBP_Veh_American_Tank"));
	TankUIClass = TankUIFinder.Class;
}

// Called when the game starts or when spawned
void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(GetPawn());

	TankUIWidget = CreateWidget<UTankWidget>(this, TankUIClass);
	if (TankUIWidget)
		TankUIWidget->AddToViewport();
}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATankPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (InputComponent)
	{
		InputComponent->BindAxis(TEXT("AimHorizontal"), this, &ATankPlayerController::AimHorizontally);
		InputComponent->BindAxis(TEXT("AimVertical"), this, &ATankPlayerController::AimVertically);
		InputComponent->BindAxis(TEXT("DriveForward"), this, &ATankPlayerController::Drive);
		InputComponent->BindAxis(TEXT("SteerRight"), this, &ATankPlayerController::Steer);

		InputComponent->BindAction(TEXT("Brake"), EInputEvent::IE_Pressed, this, &ATankPlayerController::Brake);
		InputComponent->BindAction(TEXT("Brake"), EInputEvent::IE_Released, this, &ATankPlayerController::Unbrake);
	}
	
}

void ATankPlayerController::AimHorizontally(float Val)
{
	USpringArmComponent* SpringArm = Tank->FindComponentByClass<USpringArmComponent>();
	SpringArm->AddWorldRotation(FRotator(0.0f, Val, 0.0f));
}

void ATankPlayerController::AimVertically(float Val)
{
	USpringArmComponent* SpringArm = Tank->FindComponentByClass<USpringArmComponent>();
	SpringArm->AddLocalRotation(FRotator(Val, 0.0f, 0.0f));
}

void ATankPlayerController::Brake()
{
	UTankMovementComponent* TankMovement = Tank->FindComponentByClass<UTankMovementComponent>();
	TankMovement->IntendStop();
}

void ATankPlayerController::Unbrake()
{
	UTankMovementComponent* TankMovement = Tank->FindComponentByClass<UTankMovementComponent>();
	TankMovement->UndoStop();
}

void ATankPlayerController::Drive(float Torque)
{
	UTankMovementComponent* TankMovement = Tank->FindComponentByClass<UTankMovementComponent>();
	TankMovement->IntendDriveForward(Torque);
}

void ATankPlayerController::Steer(float Torque)
{
	UTankMovementComponent* TankMovement = Tank->FindComponentByClass<UTankMovementComponent>();
	TankMovement->IntendSteerRight(Torque);
}

