// Copyright 2023 Tobias Grubenmann.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/BoxComponent.h"
#include "WindShadow.generated.h"


/**
 * Attaching this component to an actor makes it block the wind for a certain distance.
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WINDPHYSICS_API UWindShadow : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWindShadow();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	float GetBlockDistance() const;

private:
	UPROPERTY(EditAnywhere)
	float BlockDistance;
		
};
