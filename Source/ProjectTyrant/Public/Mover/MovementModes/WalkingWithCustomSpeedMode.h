// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DefaultMovementSet/Modes/WalkingMode.h"
#include "WalkingWithCustomSpeedMode.generated.h"

// Movement mode that changes the maximum walking speed of an Actor
UCLASS()
class PROJECTTYRANT_API UWalkingWithCustomSpeedMode : public UWalkingMode
{
	GENERATED_BODY()

protected:
	virtual void OnActivate() override;
	virtual void OnDeactivate() override;

private:
	UPROPERTY(EditAnywhere, meta=(ForceUnits="cm/s"))
	float MaxSpeed = 800;

	float BaseMaxSpeed = 0;
};