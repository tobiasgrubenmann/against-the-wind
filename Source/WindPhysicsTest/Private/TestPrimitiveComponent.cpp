// Copyright 2023 Tobias Grubenmann.


#include "TestPrimitiveComponent.h"


UTestPrimitiveComponent::UTestPrimitiveComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	Forces = TArray<FVector>();
}


void UTestPrimitiveComponent::AddForceAtLocation(FVector Force, FVector Location, FName BoneName)
{
	Forces.Add(Force);
}
