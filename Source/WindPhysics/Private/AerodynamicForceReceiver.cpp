// Copyright 2023 Tobias Grubenmann.


#include "AerodynamicForceReceiver.h"
#include "Kismet/GameplayStatics.h"
#include "WindComponent.h"
#include "WindShadow.h"


UAerodynamicForceReceiver::UAerodynamicForceReceiver()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UAerodynamicForceReceiver::BeginPlay()
{
	Super::BeginPlay();
	
	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	WindSubsystem = GameInstance->GetSubsystem<UWindSubsystem>();
}


void UAerodynamicForceReceiver::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get a reference to the current wind.
	UWindComponent* Wind = WindSubsystem->GetWind();

	if (TargetComponent != nullptr && BoxComponent != nullptr && Wind != nullptr)
	{
		// Create vectors for the three planes that define the aerodynamic forces.

		FVector BoxForward = GetOwner()->GetActorForwardVector() * BoxComponent->GetScaledBoxExtent().X;
		FVector BoxRight = GetOwner()->GetActorRightVector() * BoxComponent->GetScaledBoxExtent().Y;
		FVector BoxUp = GetOwner()->GetActorUpVector() * BoxComponent->GetScaledBoxExtent().Z;

		// Calculate and apply forces.

		AddAerodynamicForce(
			BoxComponent->GetComponentLocation() + BoxRight + BoxUp,
			BoxComponent->GetComponentLocation() - BoxRight + BoxUp,
			BoxComponent->GetComponentLocation() - BoxRight - BoxUp,
			BoxComponent->GetComponentLocation() + BoxRight - BoxUp,
			Wind);

		AddAerodynamicForce(
			BoxComponent->GetComponentLocation() + BoxForward + BoxUp,
			BoxComponent->GetComponentLocation() - BoxForward + BoxUp,
			BoxComponent->GetComponentLocation() - BoxForward - BoxUp,
			BoxComponent->GetComponentLocation() + BoxForward - BoxUp,
			Wind);

		AddAerodynamicForce(
			BoxComponent->GetComponentLocation() + BoxForward + BoxRight,
			BoxComponent->GetComponentLocation() - BoxForward + BoxRight,
			BoxComponent->GetComponentLocation() - BoxForward - BoxRight,
			BoxComponent->GetComponentLocation() + BoxForward - BoxRight,
			Wind);
	}
}


void UAerodynamicForceReceiver::Setup(UPrimitiveComponent* Receiver, UBoxComponent* BoxCollider)
{
	TargetComponent = Receiver;
	BoxComponent = BoxCollider;
}


void UAerodynamicForceReceiver::AddAerodynamicForce(FVector Vector1, FVector Vector2, FVector Vector3, FVector Vector4, UWindComponent* Wind)
{
	FVector RelativeVelocity = Wind->GetVelocity();
		- TargetComponent->GetPhysicsLinearVelocityAtPoint(Vector1) / 4
		- TargetComponent->GetPhysicsLinearVelocityAtPoint(Vector2) / 4
		- TargetComponent->GetPhysicsLinearVelocityAtPoint(Vector3) / 4
		- TargetComponent->GetPhysicsLinearVelocityAtPoint(Vector4) / 4;

	float RelativeVelocityMagnitude = RelativeVelocity.Length();

	if (!FMath::IsNearlyEqual(RelativeVelocityMagnitude, 0))
	{
		// Check whether corners are blocked.

		float ExposedFraction1 = GetExposedFraction(Vector1, Wind);
		float ExposedFraction2 = GetExposedFraction(Vector2, Wind);
		float ExposedFraction3 = GetExposedFraction(Vector3, Wind);
		float ExposedFraction4 = GetExposedFraction(Vector4, Wind);

		float ExposedFraction = ExposedFraction1 + ExposedFraction2 + ExposedFraction3 + ExposedFraction4;

		if (!FMath::IsNearlyEqual(ExposedFraction, 0))
		{

			FVector TriangleVector1 = Vector2 - Vector1;
			FVector TriangleVector2 = Vector3 - Vector1;
			FVector TriangleVector3 = Vector4 - Vector1;

			// Calculate normal (same for both triangles).
			FVector Normal = TriangleVector1.Cross(TriangleVector2);
			Normal.Normalize();

			// Calculate cross-sectional areas for both triangles.
			float TriangleArea1 = 0.5f * TriangleVector1.Cross(TriangleVector2).Length();
			float TriangleArea2 = 0.5f * TriangleVector2.Cross(TriangleVector3).Length();
			float CrossSectionalArea = (TriangleArea1 + TriangleArea2) * RelativeVelocity.Dot(Normal) / RelativeVelocityMagnitude * ExposedFraction / 4;

			// Aerodynamic force.
			FVector Force = 0.5f * Wind->GetDensity() * RelativeVelocityMagnitude * RelativeVelocityMagnitude * AerodynamicConstant * CrossSectionalArea * Normal;

			// Apply force.
			TargetComponent->AddForceAtLocation(Force * ExposedFraction1 / ExposedFraction, Vector1);
			TargetComponent->AddForceAtLocation(Force * ExposedFraction2 / ExposedFraction, Vector2);
			TargetComponent->AddForceAtLocation(Force * ExposedFraction3 / ExposedFraction, Vector3);
			TargetComponent->AddForceAtLocation(Force * ExposedFraction4 / ExposedFraction, Vector4);

		}
	}
}


float UAerodynamicForceReceiver::GetExposedFraction(FVector Start, UWindComponent* Wind) const
{
	float Fraction = 1;

	// Raycast.

	FCollisionQueryParams TraceParams(
		FName(TEXT("")), // No Tag.
		true, // Trace complex.
		GetOwner() // Ignore self.
	);

	FVector End = Start - Wind->GetVelocity().GetSafeNormal() * MaxTraceLength;
	TArray<FHitResult> OutHits;
	GetWorld()->LineTraceMultiByObjectType(OutHits, Start, End, FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldStatic), TraceParams);

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
