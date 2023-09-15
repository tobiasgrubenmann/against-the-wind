// Copyright 2023 Tobias Grubenmann.


#include "WindReceiver.h"
#include "Kismet/GameplayStatics.h"
#include "WindComponent.h"
#include "WindShadow.h"


UWindReceiver::UWindReceiver()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UWindReceiver::BeginPlay()
{
	Super::BeginPlay();

}


void UWindReceiver::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}


float UWindReceiver::GetExposedFraction(const FVector& Location, const FVector& WindVelocity) const
{
	float Fraction = 1;

	// Raycast.

	FCollisionQueryParams TraceParams(
		FName(TEXT("")), // No Tag.
		true, // Trace complex.
		GetOwner() // Ignore self.
	);

	FVector End = Location - WindVelocity.GetSafeNormal() * MaxTraceLength;
	TArray<FHitResult> OutHits;
	GetWorld()->LineTraceMultiByObjectType(OutHits, Location, End, FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldStatic), TraceParams);

	// Check for wind shadow.

	for (const FHitResult& Hit : OutHits)
	{
		UWindShadow* WindShadow = Hit.GetActor()->FindComponentByClass<UWindShadow>();

		if (WindShadow != nullptr)
		{
			float BlockDistance = WindShadow->GetBlockDistance();
			
			if (Hit.Distance <= BlockDistance)
			{
				Fraction = FMath::Min(Fraction, Hit.Distance / BlockDistance);
			}
		}
	}

	return Fraction;
}
