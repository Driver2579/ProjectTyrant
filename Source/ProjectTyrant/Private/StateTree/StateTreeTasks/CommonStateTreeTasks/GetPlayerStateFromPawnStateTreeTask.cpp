// Vladislav Semchuk, 2025

#include "StateTree/StateTreeTasks/CommonStateTreeTasks/GetPlayerStateFromPawnStateTreeTask.h"

#include "StateTreeExecutionContext.h"

FGetPlayerStateFromPawnStateTreeTask::FGetPlayerStateFromPawnStateTreeTask()
{
	bShouldCallTick = false;
}

EStateTreeRunStatus FGetPlayerStateFromPawnStateTreeTask::EnterState(FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition) const
{
	FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

	if (!ensureAlways(InstanceData.Pawn) || !ensureAlways(InstanceData.Pawn.IsA<APawn>()))
	{
		return EStateTreeRunStatus::Failed;
	}

	const EStateTreeRunStatus PositiveReturnStatus = InstanceData.bRunTaskForever ?
		EStateTreeRunStatus::Running : EStateTreeRunStatus::Succeeded;

	InstanceData.OutPlayerState = CastChecked<APawn>(InstanceData.Pawn)->GetPlayerState();

	return PositiveReturnStatus;
}