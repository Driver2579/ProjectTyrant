// Vladislav Semchuk, 2025

#include "StateTree/StateTreeTasks/CommonStateTreeTasks/EndLoopedMusicStateTreeTask.h"

#include "StateTreeExecutionContext.h"
#include "Components/ActorComponents/LoopedMusicManagerComponent.h"

FEndLoopedMusicStateTreeTask::FEndLoopedMusicStateTreeTask()
{
	bShouldCallTick = false;
}

EStateTreeRunStatus FEndLoopedMusicStateTreeTask::EnterState(FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition) const
{
	const FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

	const bool bLoopedMusicManagerComponentValid = ensureAlways(InstanceData.LoopedMusicManagerComponent) &&
		ensureAlways(InstanceData.LoopedMusicManagerComponent.IsA<ULoopedMusicManagerComponent>());

	if (!bLoopedMusicManagerComponentValid)
	{
		return EStateTreeRunStatus::Failed;
	}

	const EStateTreeRunStatus PositiveReturnStatus = InstanceData.bRunTaskForever ?
		EStateTreeRunStatus::Running : EStateTreeRunStatus::Succeeded;

	CastChecked<ULoopedMusicManagerComponent>(InstanceData.LoopedMusicManagerComponent)->EndMusic();

	return PositiveReturnStatus;
}