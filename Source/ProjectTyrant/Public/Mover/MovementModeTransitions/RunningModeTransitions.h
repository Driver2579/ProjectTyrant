// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MovementModeTransition.h"
#include "MoverSimulationTypes.h"
#include "RunningModeTransitions.generated.h"

/**
 * Transition that handles starting running based on input. Character must be on the ground to start running, regardless
 * of input.
 */
UCLASS()
class PROJECTTYRANT_API URunningModeStartTransition : public UBaseMovementModeTransition
{
	GENERATED_BODY()

protected:
	virtual FTransitionEvalResult OnEvaluate(const FSimulationTickParams& Params) const override;

private:
	UPROPERTY(EditAnywhere)
	FName RunningModeName = TEXT("Running");
};

// Transition that handles exiting running based on input
UCLASS()
class PROJECTTYRANT_API URunningModeEndTransition : public UBaseMovementModeTransition
{
	GENERATED_BODY()

protected:
	virtual FTransitionEvalResult OnEvaluate(const FSimulationTickParams& Params) const override;

private:
	// Mode to enter when exiting the running
	UPROPERTY(EditAnywhere)
	FName AutoExitToMode = DefaultModeNames::Walking;
};