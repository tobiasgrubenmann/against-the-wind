// Copyright 2023 Tobias Grubenmann.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WindComponent.generated.h"


/**
 * This component defines the global wind parameters. Only one component can be registered in the subsystem at the same time.
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WINDPHYSICS_API UWindComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWindComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FVector GetVelocity() const;

	float GetDensity() const;

private:
	UPROPERTY(EditAnywhere)
	FVector Velocity;

	UPROPERTY(EditAnywhere)
	float Density;
};
