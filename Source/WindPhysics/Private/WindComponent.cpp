// Copyright 2023 Tobias Grubenmann.


#include "WindComponent.h"
#include "Kismet/GameplayStatics.h"
#include "WindSubsystem.h"


UWindComponent::UWindComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UWindComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// Register wind.
	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	UWindSubsystem* WindSubsystem = GameInstance->GetSubsystem<UWindSubsystem>();
	WindSubsystem->RegisterWind(this);
}


void UWindComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}


FVector UWindComponent::GetVelocity() const
{
	return Velocity;
}


float UWindComponent::GetDensity() const
{
	return Density;
}

