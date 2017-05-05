// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class SECTION_04_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
private:
	ATank* GetPlayerTank() const;

	ATank* GetControlledTank() const;

public:
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaSeconds) override;
};
