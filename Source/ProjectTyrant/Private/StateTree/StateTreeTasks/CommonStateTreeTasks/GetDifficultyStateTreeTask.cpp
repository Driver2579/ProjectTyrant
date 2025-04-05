// Vladislav Semchuk, 2025

#include "StateTree/StateTreeTasks/CommonStateTreeTasks/GetDifficultyStateTreeTask.h"

#include "GameInstances/ProjectTyrantGameInstance.h"

FGetDifficultyStateTreeTask::FGetDifficultyStateTreeTask()
{
	bShouldCallTick = false;
}

EStateTreeRunStatus FGetDifficultyStateTreeTask::EnterState(FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition) const
{
	FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

	const EStateTreeRunStatus PositiveReturnStatus = InstanceData.bRunTaskForever ?
		EStateTreeRunStatus::Running : EStateTreeRunStatus::Succeeded;

	const UProjectTyrantGameInstance* GameInstance = Context.GetWorld()->GetGameInstance<UProjectTyrantGameInstance>();

	if (!ensureAlways(IsValid(GameInstance)))
	{
		return EStateTreeRunStatus::Failed;
	}

	InstanceData.OutDifficulty = GameInstance->GetDifficulty();

	return PositiveReturnStatus;
}