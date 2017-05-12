// Copyright EmbraceIT Ltd.

#include "Section_04.h"
#include "Public/Projectile.h"
#include "Public/TankBarrel.h"
#include "Public/TankTurret.h"
#include "Public/TankAimingComponent.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::BeginPlay()
{
	// First fire is after initial reload
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Turret = TurretToSet;
	Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Turret && Barrel)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed,
	false, 0.0f, 0.0f, ESuggestProjVelocityTraceOption::DoNotTrace);
	
	if (bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards();
	}
	//If no solution found do nothing
}

void UTankAimingComponent::Fire()
{
	if (FiringState != EFiringState::Reloading)
	{
		if (!ensure(Barrel && ProjectileBlueprint)) { return; }

		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));
		Projectile->LaunchProjectile(LaunchSpeed);

		LastFireTime = FPlatformTime::Seconds();
	}
}

void UTankAimingComponent::MoveBarrelTowards()
{
	if (!ensure(Turret && Barrel)) { return; }

	//Work-out difference between current barrel rotation and aim direction
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
	if (FMath::Abs(DeltaRotator.Yaw) > 180)
	{
		Turret->Rotate(-DeltaRotator.Yaw);
	}
	else
	{
		Turret->Rotate(DeltaRotator.Yaw);
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }

	auto BarrelDirection = Barrel->GetForwardVector();

	return !BarrelDirection.Equals(AimDirection, 0.1);
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}