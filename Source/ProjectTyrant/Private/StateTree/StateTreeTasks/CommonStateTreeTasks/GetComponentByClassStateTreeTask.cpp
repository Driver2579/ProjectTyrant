// Vladislav Semchuk, 2025

#include "StateTree/StateTreeTasks/CommonStateTreeTasks/GetComponentByClassStateTreeTask.h"

#include "StateTreeExecutionContext.h"

FGetComponentByClassStateTreeTask::FGetComponentByClassStateTreeTask()
{
	bShouldCallTick = false;
}

EStateTreeRunStatus FGetComponentByClassStateTreeTask::EnterState(FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition) const
{
	FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

	if (!ensureAlways(InstanceData.Actor) || !ensureAlways(IsValid(InstanceData.ComponentClass)))
	{
		return EStateTreeRunStatus::Failed;
	}

	const EStateTreeRunStatus PositiveReturnStatus = InstanceData.bRunTaskForever ?
		EStateTreeRunStatus::Running : EStateTreeRunStatus::Succeeded;

	InstanceData.OutComponent = InstanceData.Actor->FindComponentByClass(InstanceData.ComponentClass);

	return PositiveReturnStatus;
}