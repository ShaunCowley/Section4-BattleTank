// Copyright EmbraceIT Ltd.

#pragma once

#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class SECTION_04_API ATank : public APawn
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth = StartingHealth;

	// Sets default values for this pawn's properties
	ATank();

public:
	//Called by the engine when actor damage is dealt
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	
};
