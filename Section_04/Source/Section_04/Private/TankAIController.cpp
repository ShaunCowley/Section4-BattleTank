// Fill out your copyright notice in the Description page of Project Settings.

#include "Section_04.h"
#include "Public/TankAimingComponent.h"
#include "Public/TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (!ensure(PlayerTank && ControlledTank)) { return; }

	// Move toward the player
	MoveToActor(PlayerTank, AcceptanceRadius); //TODO check radius is in centimeters 
		
	// Aim towards the player
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	// Fire at the player
	if (AimingComponent->GetFiringState() == EFiringState::Locked)
	{
		AimingComponent->Fire();
	}
}


