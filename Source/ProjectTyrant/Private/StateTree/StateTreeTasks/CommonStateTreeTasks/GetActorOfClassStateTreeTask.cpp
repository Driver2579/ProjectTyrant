// Vladislav Semchuk, 2025

#include "StateTree/StateTreeTasks/CommonStateTreeTasks/GetActorOfClassStateTreeTask.h"

#include "StateTreeExecutionContext.h"
#include "Kismet/GameplayStatics.h"

FGetActorOfClassStateTreeTask::FGetActorOfClassStateTreeTask()
{
	bShouldCallTick = false;
}

EStateTreeRunStatus FGetActorOfClassStateTreeTask::EnterState(FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition) const
{
	const FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

	const EStateTreeRunStatus PositiveReturnStatus = InstanceData.bRunTaskForever ?
		EStateTreeRunStatus::Running : EStateTreeRunStatus::Succeeded;

#if DO_ENSURE
	ensureAlways(IsValid(InstanceData.ActorClass));
#endif

	AActor*& OutActor = *InstanceData.OutActorRef.GetMutablePtr(Context);
	OutActor = UGameplayStatics::GetActorOfClass(Context.GetOwner(), InstanceData.ActorClass);

	return OutActor ? PositiveReturnStatus : EStateTreeRunStatus::Failed;
}
