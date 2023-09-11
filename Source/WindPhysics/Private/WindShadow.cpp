// Copyright 2023 Tobias Grubenmann.


#include "WindShadow.h"


UWindShadow::UWindShadow()
{
	PrimaryComponentTick.bCanEverTick = true;

}



void UWindShadow::BeginPlay()
{
	Super::BeginPlay();
	
}


void UWindShadow::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}


float UWindShadow::GetBlockDistance() const
{
	return BlockDistance;
}
