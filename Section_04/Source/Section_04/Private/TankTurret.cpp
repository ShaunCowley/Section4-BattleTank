// Fill out your copyright notice in the Description page of Project Settings.

#include "Section_04.h"
#include "Public/TankTurret.h"

void UTankTurret::Azimuth(float RelativeSpeed)
{
	/*auto Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f -> Calling UTankTurret->Azimuth"), Time);*/

	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto AzimuthChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto NewAzimuth = RelativeRotation.Yaw + AzimuthChange;

	SetRelativeRotation(FRotator(0, NewAzimuth, 0));
}


