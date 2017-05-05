// Fill out your copyright notice in the Description page of Project Settings.

#include "Section_04.h"
#include "Public/TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	/*auto Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f -> Calling UTankTurret->Azimuth"), Time);*/

	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto NewRotation = RelativeRotation.Yaw + RotationChange;

	SetRelativeRotation(FRotator(0, NewRotation, 0));
}


