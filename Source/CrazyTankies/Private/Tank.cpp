// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "TankTurret.h"
#include "TankBarrel.h"

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Hull = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Hull"));
	Hull->SetSimulatePhysics(true);
	Hull->SetCollisionProfileName(TEXT("Vehicle"));
	RootComponent = Hull;

	LeftTrack = CreateDefaultSubobject<UTankTrack>(TEXT("LeftTrack"));
	LeftTrack->AttachToComponent(Hull, FAttachmentTransformRules::KeepRelativeTransform, TEXT("Socket_Track_l"));
	LeftTrack->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	RightTrack = CreateDefaultSubobject<UTankTrack>(TEXT("RightTrack"));
	RightTrack->AttachToComponent(Hull, FAttachmentTransformRules::KeepRelativeTransform, TEXT("Socket_Track_r"));
	RightTrack->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->AttachToComponent(Hull, FAttachmentTransformRules::KeepRelativeTransform);
	SpringArm->SetRelativeLocationAndRotation(FVector::UpVector * 300.0f, FRotator(-20.0f, 0.0f, 0.0f));
	SpringArm->TargetArmLength = 900.0f;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->AttachToComponent(SpringArm, FAttachmentTransformRules::KeepRelativeTransform);

	Movement = CreateDefaultSubobject<UTankMovementComponent>(TEXT("TankMovement"));

	bCanAffectNavigationGeneration = true;

	StartingHealth = 100;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = StartingHealth;

	PaintJob = UMaterialInstanceDynamic::Create(Hull->GetMaterial(0), this);
	Hull->SetMaterial(0, PaintJob);

	UTankTurret* Turret = FindComponentByClass<UTankTurret>();
	UTankBarrel* Barrel = FindComponentByClass<UTankBarrel>();

	if (Turret)
		Turret->SetMaterial(0, PaintJob);

	if (Barrel)
		Barrel->SetMaterial(0, PaintJob);
}


TSubclassOf<class UTankWidget> ATank::GetUI() const
{
	return UserInterface;
}

UMaterialInstanceDynamic* ATank::GetPaintJob() const
{
	return PaintJob;
}

float ATank::GetHealthPercentage() const
{
	return (float)CurrentHealth / (float)StartingHealth;
}


float ATank::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(Damage);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;
	PaintJob->SetScalarParameterValue(TEXT("DamagedAlpha"), 1.0f - GetHealthPercentage());
	
	/*
	if (CurrentHealth <= 0)
	{
		OnDeath.Broadcast();
	}
	*/

	return DamageToApply;
}

