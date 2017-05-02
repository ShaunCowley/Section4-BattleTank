// Fill out your copyright notice in the Description page of Project Settings.

#include "Section_04.h"
#include "TankAIController.h"

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr; }
	return Cast<ATank>(PlayerPawn);
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto PlayerTank = GetPlayerTank();

	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController cannot find a player tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController targetting at: %s"), *(PlayerTank->GetName()));
	}
}


