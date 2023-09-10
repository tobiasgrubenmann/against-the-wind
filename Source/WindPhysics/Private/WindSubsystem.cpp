// Copyright 2023 Tobias Grubenmann.


#include "WindSubsystem.h"


void UWindSubsystem::RegisterWind(UWindComponent* NewWind)
{
	Wind = NewWind;
}


UWindComponent* UWindSubsystem::GetWind() const
{
	return Wind;
}
