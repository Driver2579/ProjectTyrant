// Vladislav Semchuk, 2025

#include "StateTree/StateTreeTasks/CommonStateTreeTasks/GetActorsLocationsStateTreeTask.h"

#include "StateTreeExecutionContext.h"

FGetActorsLocationsStateTreeTask::FGetActorsLocationsStateTreeTask()
{
	bShouldCallTick = false;
}

EStateTreeRunStatus FGetActorsLocationsStateTreeTask::EnterState(FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition) const
{
	FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

	const EStateTreeRunStatus PositiveReturnStatus = InstanceData.bRunTaskForever ?
		EStateTreeRunStatus::Running : EStateTreeRunStatus::Succeeded;

	for (const TObjectPtr<AActor>& Actor : InstanceData.Actors)
	{
		if (ensureAlways(IsValid(Actor)))
		{
			InstanceData.OutActorsLocations.Add(Actor->GetActorLocation());
		}
	}

	return PositiveReturnStatus;
}