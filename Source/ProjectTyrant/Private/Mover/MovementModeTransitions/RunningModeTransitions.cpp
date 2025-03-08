// Fill out your copyright notice in the Description page of Project Settings.

#include "Mover/MovementModeTransitions/RunningModeTransitions.h"

#include "DefaultMovementSet/CharacterMoverComponent.h"
#include "Mover/ProjectTyrantMoverInputs.h"

FTransitionEvalResult URunningModeStartTransition::OnEvaluate(const FSimulationTickParams& Params) const
{
	FTransitionEvalResult EvalResult = FTransitionEvalResult::NoTransition;

	const UCharacterMoverComponent* CharacterMoverComponent = Cast<UCharacterMoverComponent>(
		Params.MovingComps.MoverComponent.Get());

	const bool bCanRun = ensureAlways(IsValid(CharacterMoverComponent)) && CharacterMoverComponent->IsOnGround() &&
		Params.StartState.SyncState.MovementMode != RunningModeName;

	if (!bCanRun)
	{
		return EvalResult;
	}

	const FProjectTyrantMoverInputs* MoverInputs = Params.StartState.InputCmd.InputCollection.FindDataByType<
		FProjectTyrantMoverInputs>();

	if (MoverInputs && MoverInputs->bRunPressed)
	{
		EvalResult.NextMode = RunningModeName;
	}

	return EvalResult;
}

FTransitionEvalResult URunningModeEndTransition::OnEvaluate(const FSimulationTickParams& Params) const
{
	FTransitionEvalResult EvalResult = FTransitionEvalResult::NoTransition;

	const FProjectTyrantMoverInputs* MoverInputs = Params.StartState.InputCmd.InputCollection.FindDataByType<
		FProjectTyrantMoverInputs>();

	if (ensureAlways(MoverInputs) && !MoverInputs->bRunPressed)
	{
		EvalResult.NextMode = AutoExitToMode;
	}

	return EvalResult;
}