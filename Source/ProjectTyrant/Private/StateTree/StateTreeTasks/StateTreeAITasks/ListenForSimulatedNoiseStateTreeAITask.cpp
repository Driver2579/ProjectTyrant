// Vladislav Semchuk, 2025

#include "StateTree/StateTreeTasks/StateTreeAITasks/ListenForSimulatedNoiseStateTreeAITask.h"

#include "ProjectTyrantGameplayTags.h"
#include "StateTreeExecutionContext.h"
#include "GameModes/ProjectTyrantGameMode.h"

FListenForSimulatedNoiseStateTreeAITask::FListenForSimulatedNoiseStateTreeAITask()
{
	bShouldCallTick = false;
}

EStateTreeRunStatus FListenForSimulatedNoiseStateTreeAITask::EnterState(FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition) const
{
	SetCachedInstanceDataFromContext(Context);

	FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

	AProjectTyrantGameMode* ProjectTyrantGameMode = Context.GetWorld()->GetAuthGameMode<AProjectTyrantGameMode>();

	const bool bGameModeIsValid = ensureAlwaysMsgf(IsValid(ProjectTyrantGameMode),
		TEXT("The selected GameMode must be a ProjectTyrantGameMode!"));

	if (!bGameModeIsValid)
	{
		return EStateTreeRunStatus::Failed;
	}

	InstanceData.OnPlayerMadeNoiseDelegateHandle = ProjectTyrantGameMode->OnPlayerMadeNoise.AddRaw(this,
		&FListenForSimulatedNoiseStateTreeAITask::OnPlayerMadeNoise);

	return EStateTreeRunStatus::Running;
}

void FListenForSimulatedNoiseStateTreeAITask::ExitState(FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition) const
{
	const FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

	AProjectTyrantGameMode* ProjectTyrantGameMode = Context.GetWorld()->GetAuthGameMode<AProjectTyrantGameMode>();

	// Unsubscribe from the event
	if (IsValid(ProjectTyrantGameMode))
	{
		ProjectTyrantGameMode->OnPlayerMadeNoise.Remove(InstanceData.OnPlayerMadeNoiseDelegateHandle);
	}

	ClearCachedInstanceData();

	FStateTreeTaskCommonBase::ExitState(Context, Transition);
}

void FListenForSimulatedNoiseStateTreeAITask::SetCachedInstanceDataFromContext(
	const FStateTreeExecutionContext& Context) const
{
	WeakInstanceStorage = Context.GetMutableInstanceData()->GetWeakMutableStorage();
	CachedOwner = Context.GetOwner();
}

void FListenForSimulatedNoiseStateTreeAITask::ClearCachedInstanceData() const
{
	WeakInstanceStorage = nullptr;
	CachedOwner = nullptr;
}

void FListenForSimulatedNoiseStateTreeAITask::OnPlayerMadeNoise() const
{
	const TSharedPtr<FStateTreeInstanceStorage> InstanceStorage = WeakInstanceStorage.Pin();

	if (ensureAlways(InstanceStorage.IsValid()))
	{
		InstanceStorage->GetMutableEventQueue().SendEvent(CachedOwner,
			ProjectTyrantGameplayTags::StateTree_Event_AI_HeardPlayer);
	}
}