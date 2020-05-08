// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

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
	LeftTrack->SetCollisionProfileName(TEXT("Default"));

	RightTrack = CreateDefaultSubobject<UTankTrack>(TEXT("RightTrack"));
	RightTrack->AttachToComponent(Hull, FAttachmentTransformRules::KeepRelativeTransform, TEXT("Socket_Track_r"));
	RightTrack->SetCollisionProfileName(TEXT("Default"));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->AttachToComponent(Hull, FAttachmentTransformRules::KeepRelativeTransform, TEXT("Socket_Turret"));
	SpringArm->SetRelativeRotation(FRotator(-20.0f, 0.0f, 0.0f));
	SpringArm->TargetArmLength = 1000.0f;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->AttachToComponent(SpringArm, FAttachmentTransformRules::KeepRelativeTransform);

	Movement = CreateDefaultSubobject<UTankMovementComponent>(TEXT("TankMovement"));
}