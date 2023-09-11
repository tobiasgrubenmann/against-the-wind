// Copyright 2023 Tobias Grubenmann.


#include "TestAerodynamicForceReceiver.h"


UTestAerodynamicForceReceiver::UTestAerodynamicForceReceiver()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UTestAerodynamicForceReceiver::SetExposedFraction(TMap<FVector, float> FractionsMap)
{
	Fractions = TMap<FVector, float>(FractionsMap);
}


float UTestAerodynamicForceReceiver::GetExposedFraction(FVector Location, FVector WindVelocity) const
{
	float Fraction = 0;

	TArray<FVector> Keys;
	Fractions.GetKeys(Keys);
	for (FVector Key : Keys)
	{
		if (FMath::IsNearlyZero((Key - Location).SquaredLength()))
		{
			Fraction = Fractions[Key];
			break;
		}
	}

	return Fraction;
}
