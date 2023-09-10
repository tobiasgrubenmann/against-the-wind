// Copyright 2023 Tobias Grubenmann.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "WindComponent.h"
#include "WindSubsystem.generated.h"

/**
 * Facilitates coordination between wind and the receivers of aerodynamic forces.
 */
UCLASS()
class WINDPHYSICS_API UWindSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	void RegisterWind(UWindComponent* NewWind);

	UWindComponent* GetWind() const;

private:
	TObjectPtr<UWindComponent> Wind;
	
};
