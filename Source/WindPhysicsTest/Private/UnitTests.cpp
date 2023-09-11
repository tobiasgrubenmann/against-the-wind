// Copyright 2023 Tobias Grubenmann.


#include "Misc/AutomationTest.h"
#include "Tests/AutomationEditorCommon.h"
#include "UObject/UnrealType.h"
#include "TestAerodynamicForceReceiver.h"
#include "TestPrimitiveComponent.h"


#if WITH_DEV_AUTOMATION_TESTS

IMPLEMENT_SIMPLE_AUTOMATION_TEST(UnitTests, "Wind.AerodynamicForceReceiver", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)


bool UnitTests::RunTest(const FString& Parameters)
{
	float Tolerance = 0.00001;

	FVector Vector1 = FVector(0, 0, 0);
	FVector Vector2 = FVector(0, 1, 0);
	FVector Vector3 = FVector(0, 1, 1);
	FVector Vector4 = FVector(0, 0, 1);

	auto CreateTestActor = [](TMap<FVector, float> Fractions)
	{
		AActor* Actor = NewObject<AActor>();
		USceneComponent* Root = Cast<USceneComponent>(Actor->CreateComponentFromTemplate(NewObject<USceneComponent>()));
		Actor->SetRootComponent(Root);
		UTestAerodynamicForceReceiver* AerodynamicForceReceiver = Cast<UTestAerodynamicForceReceiver>(Actor->CreateComponentFromTemplate(NewObject<UTestAerodynamicForceReceiver>()));
		Actor->AddInstanceComponent(AerodynamicForceReceiver);
		AerodynamicForceReceiver->SetExposedFraction(Fractions);
		UTestPrimitiveComponent* TestPrimitiveComponent = Cast<UTestPrimitiveComponent>(Actor->CreateComponentFromTemplate(NewObject<UTestPrimitiveComponent>()));
		Actor->AddInstanceComponent(TestPrimitiveComponent);
		AerodynamicForceReceiver->Setup(TestPrimitiveComponent, nullptr);
		return Actor;
	};

	// Complete frontal exposure.
	{
		// Arrange
		TMap<FVector, float> Fractions = { {Vector1, 1}, {Vector2, 1}, {Vector3, 1}, {Vector4, 1} };
		AActor* Actor = CreateTestActor(Fractions);
		UAerodynamicForceReceiver* AerodynamicForceReceiver = Actor->FindComponentByClass<UAerodynamicForceReceiver>();
		UTestPrimitiveComponent* TestPrimitiveComponent = Actor->FindComponentByClass<UTestPrimitiveComponent>();

		// Act
		AerodynamicForceReceiver->AddAerodynamicForce(Vector1, Vector2, Vector3, Vector4, FVector(1, 0, 0), 1.f, 1.f);

		// Assert
		TestEqual(TEXT("Complete frontal exposure: Force at first vertex of plane."), TestPrimitiveComponent->Forces[0], FVector(1 / 8.f, 0, 0), Tolerance);
		TestEqual(TEXT("Complete frontal exposure: Force at second vertex of plane."), TestPrimitiveComponent->Forces[1], FVector(1 / 8.f, 0, 0), Tolerance);
		TestEqual(TEXT("Complete frontal exposure: Force at third vertex of plane."), TestPrimitiveComponent->Forces[2], FVector(1 / 8.f, 0, 0), Tolerance);
		TestEqual(TEXT("Complete frontal exposure: Force at fourth vertex of plane."), TestPrimitiveComponent->Forces[3], FVector(1 / 8.f, 0, 0), Tolerance);
	}

	// Partial frontal exposure.
	{
		// Arrange
		TMap<FVector, float> Fractions = { {Vector1, 1}, {Vector2, 1}, {Vector3, 0}, {Vector4, 1} };
		AActor* Actor = CreateTestActor(Fractions);
		UAerodynamicForceReceiver* AerodynamicForceReceiver = Actor->FindComponentByClass<UAerodynamicForceReceiver>();
		UTestPrimitiveComponent* TestPrimitiveComponent = Actor->FindComponentByClass<UTestPrimitiveComponent>();

		// Act
		AerodynamicForceReceiver->AddAerodynamicForce(Vector1, Vector2, Vector3, Vector4, FVector(1, 0, 0), 1.f, 1.f);

		// Assert
		TestEqual(TEXT("Partial frontal exposure: Force at first vertex of plane."), TestPrimitiveComponent->Forces[0], FVector(1 / 8.f, 0, 0), Tolerance);
		TestEqual(TEXT("Partial frontal exposure: Force at second vertex of plane."), TestPrimitiveComponent->Forces[1], FVector(1 / 8.f, 0, 0), Tolerance);
		TestEqual(TEXT("Partial frontal exposure: Force at third vertex of plane."), TestPrimitiveComponent->Forces[2], FVector(0, 0, 0), Tolerance);
		TestEqual(TEXT("Partial frontal exposure: Force at fourth vertex of plane."), TestPrimitiveComponent->Forces[3], FVector(1 / 8.f, 0, 0), Tolerance);
	}

	// Fractional frontal exposure.
	{
		// Arrange
		TMap<FVector, float> Fractions = { {Vector1, 0.1f}, {Vector2, 0.2f}, {Vector3, 0.3f}, {Vector4, 0.4f} };
		AActor* Actor = CreateTestActor(Fractions);
		UAerodynamicForceReceiver* AerodynamicForceReceiver = Actor->FindComponentByClass<UAerodynamicForceReceiver>();
		UTestPrimitiveComponent* TestPrimitiveComponent = Actor->FindComponentByClass<UTestPrimitiveComponent>();

		// Act
		AerodynamicForceReceiver->AddAerodynamicForce(Vector1, Vector2, Vector3, Vector4, FVector(1, 0, 0), 1.f, 1.f);

		// Assert
		TestEqual(TEXT("Fractional frontal exposure: Force at first vertex of plane."), TestPrimitiveComponent->Forces[0], FVector(1 / 80.f, 0, 0), Tolerance);
		TestEqual(TEXT("Fractional frontal exposure: Force at second vertex of plane."), TestPrimitiveComponent->Forces[1], FVector(2 / 80.f, 0, 0), Tolerance);
		TestEqual(TEXT("Fractional frontal exposure: Force at third vertex of plane."), TestPrimitiveComponent->Forces[2], FVector(3 / 80.f, 0, 0), Tolerance);
		TestEqual(TEXT("Fractional frontal exposure: Force at fourth vertex of plane."), TestPrimitiveComponent->Forces[3], FVector(4 / 80.f, 0, 0), Tolerance);
	}

	// Complete side exposure.
	{
		// Arrange
		TMap<FVector, float> Fractions = { {Vector1, 1}, {Vector2, 1}, {Vector3, 1}, {Vector4, 1} };
		AActor* Actor = CreateTestActor(Fractions);
		UAerodynamicForceReceiver* AerodynamicForceReceiver = Actor->FindComponentByClass<UAerodynamicForceReceiver>();
		UTestPrimitiveComponent* TestPrimitiveComponent = Actor->FindComponentByClass<UTestPrimitiveComponent>();

		// Act
		AerodynamicForceReceiver->AddAerodynamicForce(Vector1, Vector2, Vector3, Vector4, FVector(1, 1, 0), 1.f, 1.f);

		// Assert
		TestEqual(TEXT("Complete side exposure: Force at first vertex of plane."), TestPrimitiveComponent->Forces[0], FVector(1.414214f / 8.f, 0, 0), Tolerance);
		TestEqual(TEXT("Complete side exposure: Force at second vertex of plane."), TestPrimitiveComponent->Forces[1], FVector(1.414214f / 8.f, 0, 0), Tolerance);
		TestEqual(TEXT("Complete side exposure: Force at third vertex of plane."), TestPrimitiveComponent->Forces[2], FVector(1.414214f / 8.f, 0, 0), Tolerance);
		TestEqual(TEXT("Complete side exposure: Force at fourth vertex of plane."), TestPrimitiveComponent->Forces[3], FVector(1.414214f / 8.f, 0, 0), Tolerance);
	}

	return true;
}

#endif //WITH_DEV_AUTOMATION_TESTS
