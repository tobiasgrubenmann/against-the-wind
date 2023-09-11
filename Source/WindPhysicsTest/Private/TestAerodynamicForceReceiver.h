// Copyright 2023 Tobias Grubenmann.

#pragma once

#include "CoreMinimal.h"
#include "AerodynamicForceReceiver.h"
#include "TestAerodynamicForceReceiver.generated.h"


/**
 * Replaces the GetExposedFraction() method for testing.
 */
UCLASS()
class WINDPHYSICSTEST_API UTestAerodynamicForceReceiver : public UAerodynamicForceReceiver
{
	GENERATED_BODY()

public:
	UTestAerodynamicForceReceiver();

	void SetExposedFraction(TMap<FVector, float> FractionsMap);

	float GetExposedFraction(FVector Location, FVector WindVelocity) const override;

private:
	UPROPERTY()
	TMap<FVector, float> Fractions;
		
};
