// Copyright 2023 Tobias Grubenmann.


#include "AerodynamicForceReceiver.h"
#include "Kismet/GameplayStatics.h"
#include "WindComponent.h"


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
	FVector RelativeVelocity1 = TargetComponent->GetPhysicsLinearVelocityAtPoint(Vector1) / 4;

	FVector RelativeVelocity = Wind->GetVelocity();
		- RelativeVelocity1//TargetComponent->GetPhysicsLinearVelocityAtPoint(Vector1) / 4
		- TargetComponent->GetPhysicsLinearVelocityAtPoint(Vector2) / 4
		- TargetComponent->GetPhysicsLinearVelocityAtPoint(Vector3) / 4
		- TargetComponent->GetPhysicsLinearVelocityAtPoint(Vector4) / 4;

	float RelativeVelocityMagnitude = RelativeVelocity.Length();

	if (!FMath::IsNearlyEqual(RelativeVelocityMagnitude, 0))
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
		float CrossSectionalArea = (TriangleArea1 + TriangleArea2) * RelativeVelocity.Dot(Normal) / RelativeVelocityMagnitude;

		// Aerodynamic force.
		FVector Force = 0.5f * Wind->GetDensity() * RelativeVelocityMagnitude * RelativeVelocityMagnitude * AerodynamicConstant * CrossSectionalArea * Normal;

		// Apply force.
		TargetComponent->AddForceAtLocation(Force / 4, Vector1);
		TargetComponent->AddForceAtLocation(Force / 4, Vector2);
		TargetComponent->AddForceAtLocation(Force / 4, Vector3);
		TargetComponent->AddForceAtLocation(Force / 4, Vector4);
	}
}
