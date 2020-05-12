// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Tank.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	AimingState = EAimingState::Aiming;
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	ATank* Tank = Cast<ATank>(GetOwner());
	Turret = Tank->FindComponentByClass<UTankTurret>();
	Barrel = Tank->FindComponentByClass<UTankBarrel>();
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsBarrelLocked())
		AimingState = EAimingState::Locked;
	else
		AimingState = EAimingState::Aiming;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Socket_Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		Barrel->LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace // Parameter must be present to prevent bug
	);

	if (bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
}

EAimingState UTankAimingComponent::GetAimingState() const
{
	return AimingState;
}

void UTankAimingComponent::MoveBarrelTowards(FVector TargetDirection)
{
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotator = TargetDirection.Rotation();

	Turret->Rotate(BarrelRotator, AimAsRotator);
	Turret->ElevateBarrel(BarrelRotator, AimAsRotator);
}

bool UTankAimingComponent::IsBarrelLocked()
{
	bool bLockedTurret;

	FVector BarrelForward = Barrel->GetForwardVector();

	if (!(Turret->GetMinElevationDegrees() == 0 && Turret->GetMaxElevationDegrees() == 0))
		bLockedTurret = BarrelForward.Equals(AimDirection, 0.01);
	else
	{
		bLockedTurret = UKismetMathLibrary::NearlyEqual_FloatFloat(BarrelForward.Y, AimDirection.Y, 0.05f) &&
						UKismetMathLibrary::NearlyEqual_FloatFloat(BarrelForward.X, AimDirection.X, 0.05f);
	}

	return bLockedTurret;
}