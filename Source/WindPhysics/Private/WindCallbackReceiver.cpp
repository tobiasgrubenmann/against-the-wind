// Copyright 2023 Tobias Grubenmann.


#include "WindCallbackReceiver.h"
#include "Kismet/GameplayStatics.h"
#include "WindComponent.h"
#include "WindShadow.h"


UWindCallbackReceiver::UWindCallbackReceiver()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UWindCallbackReceiver::BeginPlay()
{
	Super::BeginPlay();
	
	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(GetWorld());
	WindSubsystem = GameInstance->GetSubsystem<UWindSubsystem>();
}


void UWindCallbackReceiver::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get a reference to the current wind.
	UWindComponent* Wind = WindSubsystem->GetWind();

	if (Wind != nullptr)
	{
		float Fraction = GetExposedFraction(GetOwner()->GetActorLocation() + LocalExposureOffset, Wind->GetVelocity());

		ReceiveWind(Fraction * Wind->GetVelocity());
	}
}
