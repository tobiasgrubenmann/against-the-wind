// Copyright 2023 Tobias Grubenmann.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WindReceiver.generated.h"


/**
 * Base class for components that receive wind.
 */
UCLASS( ABSTRACT )
class WINDPHYSICS_API UWindReceiver : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWindReceiver();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UPROPERTY(EditAnywhere)
	float MaxTraceLength;

public:

	virtual float GetExposedFraction(FVector Location, FVector WindVelocity) const;
		
};
