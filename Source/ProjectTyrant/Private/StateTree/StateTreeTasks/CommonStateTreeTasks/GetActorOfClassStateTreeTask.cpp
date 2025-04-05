// Vladislav Semchuk, 2025

#include "StateTree/StateTreeTasks/CommonStateTreeTasks/GetActorOfClassStateTreeTask.h"

#include "StateTreeExecutionContext.h"
#include "Kismet/GameplayStatics.h"

EStateTreeRunStatus FGetActorOfClassStateTreeTask::EnterState(FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition) const
{
	const FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

	AActor*& OutActor = *InstanceData.OutActorRef.GetMutablePtr(Context);
	OutActor = UGameplayStatics::GetActorOfClass(Context.GetOwner(), InstanceData.ActorClass);

	return OutActor ? EStateTreeRunStatus::Running : EStateTreeRunStatus::Failed;
}