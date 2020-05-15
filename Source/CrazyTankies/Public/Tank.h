// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "TankMovementComponent.h"
#include "TankAimingComponent.h"
#include "TankTrack.h"
#include "TankWidget.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class CRAZYTANKIES_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	float GetHealthPercentage() const;
	UMaterialInstanceDynamic* GetPaintJob() const;

	TSubclassOf<class UTankWidget> GetUI() const;

	FVector GetFirstPersonPosition() const;
	FRotator GetFirstPesrsonRotation() const;

	FTankDelegate OnDeath;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* Hull;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UTankTrack* LeftTrack;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UTankTrack* RightTrack;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* ThirdPersonCamera;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UTankMovementComponent* Movement;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UTankWidget> UserInterface;


private:
	virtual void BeginPlay() override;

	UPROPERTY(Category = "Health", EditDefaultsOnly)
	int32 StartingHealth;

	UPROPERTY(Category = "Health", VisibleAnywhere)
	int32 CurrentHealth;

	UPROPERTY(Category = "Health", VisibleDefaultsOnly)
	class UParticleSystemComponent* OnFireFX;

	UPROPERTY(Category = "Camera", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FVector FirstPersonPosition;

	UPROPERTY(Category = "Camera", EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	FRotator FirstPersonRotation;

	class UMaterialInstanceDynamic* PaintJob;

};