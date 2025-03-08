// Fill out your copyright notice in the Description page of Project Settings.

#include "Mover/MovementModes/WalkingWithCustomSpeedMode.h"

#include "MoverComponent.h"
#include "DefaultMovementSet/Settings/CommonLegacyMovementSettings.h"

void UWalkingWithCustomSpeedMode::OnActivate()
{
	Super::OnActivate();

	UCommonLegacyMovementSettings* SharedSettings = GetMoverComponent()->FindSharedSettings_Mutable<
		UCommonLegacyMovementSettings>();

	if (ensureAlways(IsValid(SharedSettings)))
	{
		BaseMaxSpeed = SharedSettings->MaxSpeed;
		SharedSettings->MaxSpeed = MaxSpeed;
	}
}

void UWalkingWithCustomSpeedMode::OnDeactivate()
{
	Super::OnDeactivate();

	UCommonLegacyMovementSettings* SharedSettings = GetMoverComponent()->FindSharedSettings_Mutable<
		UCommonLegacyMovementSettings>();

	if (ensureAlways(IsValid(SharedSettings)))
	{
		SharedSettings->MaxSpeed = BaseMaxSpeed;
	}
}
