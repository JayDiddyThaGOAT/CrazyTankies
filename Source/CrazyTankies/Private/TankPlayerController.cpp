// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "TankAimingComponent.h"
#include "Projectile.h"
#include "Tank.h"

ATankPlayerController::ATankPlayerController()
{
	CrossHairLocationX = 0.5f;
	CrossHairLocationY = 0.333f;
	LineTraceRange = 1000000.0f;

}

// Called when the game starts or when spawned
void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(GetPawn());

	TankUIWidget = CreateWidget<UTankWidget>(this, Tank->GetUI());
	if (TankUIWidget)
	{
		TankUIWidget->AddToViewport();

		FInputModeGameOnly InputModeData;
		InputModeData.SetConsumeCaptureMouseDown(true);
		SetInputMode(InputModeData);
	}

}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto ControlledTank = Cast<ATank>(GetPawn());
		if (!ControlledTank)
			return;

		//TODO Subscribe our local method to tank death's event
		ControlledTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnControlledTankDeath);
	}
}

void ATankPlayerController::OnControlledTankDeath()
{
	TankUIWidget->RemoveFromViewport();
	FInputModeUIOnly InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	bShowMouseCursor = true;
	SetInputMode(InputModeData);

	TArray<AActor*> Tanks;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATank::StaticClass(), Tanks);
	for (int i = 0; i < Tanks.Num(); i++)
	{
		ATank* CurrentTank = Cast<ATank>(Tanks[i]);
		CurrentTank->FindComponentByClass<UTankMovementComponent>()->IntendStop();

		if (CurrentTank != Tank)
			CurrentTank->DetachFromControllerPendingDestroy();
	}
}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
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

		InputComponent->BindAction(TEXT("FireOutOfBarrel"), EInputEvent::IE_Pressed, this, &ATankPlayerController::ShootBarrelProjectile);
	}
	
}

void ATankPlayerController::ShootBarrelProjectile()
{
	UTankBarrel* Barrel = Tank->FindComponentByClass<UTankBarrel>();
	UTankAimingComponent* AimingComponent = Tank->FindComponentByClass<UTankAimingComponent>();

	if (AimingComponent->GetAimingState() == EAimingState::Locked)
		Barrel->FireProjectile();
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

void ATankPlayerController::AimTowardsCrosshair()
{
	UTankAimingComponent* TankAiming = Tank->FindComponentByClass<UTankAimingComponent>();
	UTankBarrel* Barrel = Tank->FindComponentByClass<UTankBarrel>();

	FVector HitLocation;
	bool bGotHitLocation = GetSightRayHitLocation(HitLocation);
	if (bGotHitLocation)
	{
		TankAiming->AimAt(HitLocation);

		float CrosshairOpacity;
		if (TankAiming->GetAimingState() == EAimingState::Locked && Barrel->GetFiringState() == EFiringState::Ready)
			CrosshairOpacity = 1.0f;
		else
			CrosshairOpacity = 0.25f;

		TankUIWidget->SetCrosshairColor(FLinearColor(1.0f, 1.0f, 1.0f, CrosshairOpacity));
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrossHairLocationX, ViewportSizeY * CrossHairLocationY);

	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		return GetLookVectorHitLocation(LookDirection, HitLocation);
	}

	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation; // To be discarded
	return  DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y,
		CameraWorldLocation,
		LookDirection
	);

}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Camera)
		)
	{
		if (HitResult.Actor == GetPawn())
		{
			HitLocation = FVector(0);
			return false;
		}

		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false; // Line trace didn't succeed
}
