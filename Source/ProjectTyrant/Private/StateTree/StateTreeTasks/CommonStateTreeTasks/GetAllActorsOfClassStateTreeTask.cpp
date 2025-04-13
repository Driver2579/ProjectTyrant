// Vladislav Semchuk, 2025

#include "StateTree/StateTreeTasks/CommonStateTreeTasks/GetAllActorsOfClassStateTreeTask.h"

#include "StateTreeExecutionContext.h"
#include "Kismet/GameplayStatics.h"

FGetAllActorsOfClassStateTreeTask::FGetAllActorsOfClassStateTreeTask()
{
	bShouldCallTick = false;
}

EStateTreeRunStatus FGetAllActorsOfClassStateTreeTask::EnterState(FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition) const
{
	FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

	const EStateTreeRunStatus PositiveReturnStatus = InstanceData.bRunTaskForever ?
		EStateTreeRunStatus::Running : EStateTreeRunStatus::Succeeded;

#if DO_ENSURE
	ensureAlways(IsValid(InstanceData.ActorClass));
#endif

	UGameplayStatics::GetAllActorsOfClass(Context.GetOwner(), InstanceData.ActorClass,
		InstanceData.OutActors);

	return !InstanceData.OutActors.IsEmpty() ? PositiveReturnStatus : EStateTreeRunStatus::Failed;
}