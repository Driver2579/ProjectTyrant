// Vladislav Semchuk, 2025

#include "StateTree/StateTreeTasks/CommonStateTreeTasks/GetActorLocationStateTreeTask.h"

#include "StateTreeExecutionContext.h"

FGetActorLocationStateTreeTask::FGetActorLocationStateTreeTask()
{
	bShouldCallTick = false;
}

EStateTreeRunStatus FGetActorLocationStateTreeTask::EnterState(FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition) const
{
	FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

	const EStateTreeRunStatus PositiveReturnStatus = InstanceData.bRunTaskForever ?
		EStateTreeRunStatus::Running : EStateTreeRunStatus::Succeeded;

	if (!ensureAlways(IsValid(InstanceData.Actor)))
	{
		return EStateTreeRunStatus::Failed;
	}

	InstanceData.OutActorLocation = InstanceData.Actor->GetActorLocation();

	return PositiveReturnStatus;
}