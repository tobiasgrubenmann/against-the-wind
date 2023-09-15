// Copyright 2023 Tobias Grubenmann.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WindSubsystem.h"
#include "WindReceiver.h"
#include "WindCallbackReceiver.generated.h"


/**
 * Every actor having this component will experience aerodynamic forces.
 */
UCLASS( ABSTRACT, Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WINDPHYSICS_API UWindCallbackReceiver : public UWindReceiver
{
	GENERATED_BODY()

public:	
	UWindCallbackReceiver();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UPROPERTY()
	TObjectPtr<UWindSubsystem> WindSubsystem;

	UPROPERTY(EditAnywhere)
	FVector LocalExposureOffset;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveWind(const FVector& EffectiveWind);
		
};
