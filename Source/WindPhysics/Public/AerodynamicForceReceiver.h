// Copyright 2023 Tobias Grubenmann.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/BoxComponent.h"
#include "WindSubsystem.h"
#include "WindReceiver.h"
#include "AerodynamicForceReceiver.generated.h"


/**
 * Every actor having this component will experience aerodynamic forces.
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WINDPHYSICS_API UAerodynamicForceReceiver : public UWindReceiver
{
	GENERATED_BODY()

public:	
	UAerodynamicForceReceiver();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Setup(UPrimitiveComponent* Receiver, UBoxComponent* BoxCollider);

private:

	UPROPERTY()
	TObjectPtr<UWindSubsystem> WindSubsystem;

	UPROPERTY()
	TObjectPtr<UPrimitiveComponent> TargetComponent;

	UPROPERTY()
	TObjectPtr<UBoxComponent> BoxComponent;

	UPROPERTY(EditAnywhere)
	float AerodynamicConstant;

public:
	virtual void AddAerodynamicForce(
		const FVector& Vector1,
		const FVector& Vector2,
		const FVector& Vector3,
		const FVector& Vector4,
		const FVector& WindVelocity,
		float WindDensity,
		float AerodynamicConstant);
		
};
