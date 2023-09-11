// Copyright 2023 Tobias Grubenmann.

#pragma once

#include "CoreMinimal.h"
#include "Components/PrimitiveComponent.h"
#include "TestPrimitiveComponent.generated.h"


/**
 * Replaces the AddForceAtLocation() method for testing.
 */
UCLASS()
class WINDPHYSICSTEST_API UTestPrimitiveComponent : public UPrimitiveComponent
{
	GENERATED_BODY()

public:
	UTestPrimitiveComponent();

	void AddForceAtLocation(FVector Force, FVector Location, FName BoneName) override;

	TArray<FVector> Forces;
		
};
