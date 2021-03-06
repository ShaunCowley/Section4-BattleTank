// Copyright EmbraceIT Ltd.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must be the last include

class UTankAimingComponent;

/**
 * Responsible for helping the player aim.
 */
UCLASS()
class SECTION_04_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation = 0.5f;
	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = 0.33333f;
	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000.0f;

	virtual void BeginPlay() override;

	virtual void SetPawn(APawn* InPawn) override;

	virtual void Tick(float DeltaSeconds) override;

	//Start the tank moving the barrel so that a shot would hit where the crosshair intersects the world
	void AimTowardsCrosshair();

	//Return an OUT parameter, true if hit landscape
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

	UFUNCTION()
	void OnTankDeath();

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimingCompRef);

};
