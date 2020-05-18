// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;

	UVOffset = 0.0f;
	TreadDirection = 0;
}

void UTankTrack::BeginPlay()
{
	TrackLength = GetStaticMesh()->GetBounds().GetBox().GetSize().X;
	Tread = CreateDynamicMaterialInstance(0);
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UVOffset = UVOffset + ((TreadSpeed * TreadDirection) / TrackLength);
	Tread->SetScalarParameterValue(TEXT("TreadUVOffset"), UVOffset);
}