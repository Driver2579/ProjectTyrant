// Vladislav Semchuk, 2025

#include "StateTree/StateTreeTasks/CommonStateTreeTasks/LoseGameStateTreeTask.h"

#include "GameModes/ProjectTyrantGameMode.h"

FLoseGameStateTreeTask::FLoseGameStateTreeTask()
{
	bShouldCallTick = false;
}

EStateTreeRunStatus FLoseGameStateTreeTask::EnterState(FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition) const
{
	const FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

	const APawn* CastedPlayerPawn = Cast<APawn>(InstanceData.PlayerPawn);

	if (!ensureAlwaysMsgf(CastedPlayerPawn, TEXT("PlayerPawn is invalid or is not a Pawn!")))
	{
		return EStateTreeRunStatus::Failed;
	}

	APlayerController* PlayerController = CastedPlayerPawn->GetController<APlayerController>();

	if (!ensureAlwaysMsgf(IsValid(PlayerController), TEXT("Passed PlayerPawn has no PlayerController!")))
	{
		return EStateTreeRunStatus::Failed;
	}

	AProjectTyrantGameMode* ProjectTyrantGameMode = Context.GetWorld()->GetAuthGameMode<AProjectTyrantGameMode>();

	if (!ensureAlways(ProjectTyrantGameMode))
	{
		return EStateTreeRunStatus::Failed;
	}

	ProjectTyrantGameMode->Lose(PlayerController);

	return EStateTreeRunStatus::Succeeded;
}
