// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TankWidget.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 *
 */
UCLASS()
class CRAZYTANKIES_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ATankPlayerController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupInputComponent() override;

private:
	void AimHorizontally(float Val);
	void AimVertically(float Val);
	void Steer(float Torque);
	void Drive(float Torque);
	void Brake();
	void Unbrake();

protected:
	TSubclassOf<class UTankWidget> TankUIClass;
	class UTankWidget* TankUIWidget;
	class ATank* Tank;

private:
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector& HitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;
	float CrossHairLocationX, CrossHairLocationY;
	float LineTraceRange;
};