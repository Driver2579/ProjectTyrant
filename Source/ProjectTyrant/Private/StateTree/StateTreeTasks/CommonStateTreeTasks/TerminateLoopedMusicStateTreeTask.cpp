// Vladislav Semchuk, 2025

#include "StateTree/StateTreeTasks/CommonStateTreeTasks/TerminateLoopedMusicStateTreeTask.h"

#include "StateTreeExecutionContext.h"
#include "Components/ActorComponents/LoopedMusicManagerComponent.h"

FTerminateLoopedMusicStateTreeTask::FTerminateLoopedMusicStateTreeTask()
{
	bShouldCallTick = false;
}

EStateTreeRunStatus FTerminateLoopedMusicStateTreeTask::EnterState(FStateTreeExecutionContext& Context,
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

	CastChecked<ULoopedMusicManagerComponent>(InstanceData.LoopedMusicManagerComponent)->TerminateMusic();

	return PositiveReturnStatus;
}