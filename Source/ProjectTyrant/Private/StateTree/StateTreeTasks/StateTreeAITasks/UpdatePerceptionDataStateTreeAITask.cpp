// Vladislav Semchuk, 2025

#include "StateTree/StateTreeTasks/StateTreeAITasks/UpdatePerceptionDataStateTreeAITask.h"

#include "AIController.h"
#include "ProjectTyrantGameplayTags.h"
#include "StateTreeExecutionContext.h"
#include "Components/AIPerceptionComponents/ProjectTyrantAIPerceptionComponent.h"
#include "Perception/AIPerceptionComponent.h"

FUpdatePerceptionDataStateTreeAITask::FUpdatePerceptionDataStateTreeAITask()
{
	bShouldCallTick = false;
}

EStateTreeRunStatus FUpdatePerceptionDataStateTreeAITask::EnterState(FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition) const
{
	SetCachedInstanceDataFromContext(Context);

	FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

	UProjectTyrantAIPerceptionComponent* PerceptionComponent = Cast<UProjectTyrantAIPerceptionComponent>(
		InstanceData.AIController->GetPerceptionComponent());

	const bool bPerceptionComponentIsValid = ensureAlwaysMsgf(IsValid(PerceptionComponent),
		TEXT("There is no perception component on the AIController or it has a wrong type. It's expected to "
			"be of type UProjectTyrantAIPerceptionComponent!"));

	if (!bPerceptionComponentIsValid)
	{
		return EStateTreeRunStatus::Failed;
	}

	InstanceData.OnTargetPerceptionUpdatedDelegateHandle = PerceptionComponent->OnTargetPerceptionUpdatedStatic.AddRaw(
		this, &FUpdatePerceptionDataStateTreeAITask::OnTargetPerceptionUpdated);

	return EStateTreeRunStatus::Running;
}

void FUpdatePerceptionDataStateTreeAITask::ExitState(FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition) const
{
	const FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

	UProjectTyrantAIPerceptionComponent* PerceptionComponent = Cast<UProjectTyrantAIPerceptionComponent>(
		InstanceData.AIController->GetPerceptionComponent());

	// Unsubscribe from the event
	if (IsValid(PerceptionComponent))
	{
		PerceptionComponent->OnTargetPerceptionUpdatedStatic.Remove(
			InstanceData.OnTargetPerceptionUpdatedDelegateHandle);
	}

	ClearCachedInstanceData();

	FStateTreeTaskCommonBase::ExitState(Context, Transition);
}

void FUpdatePerceptionDataStateTreeAITask::SetCachedInstanceDataFromContext(
	const FStateTreeExecutionContext& Context) const
{
	WeakInstanceStorage = Context.GetMutableInstanceData()->GetWeakMutableStorage();
	CachedOwner = Context.GetOwner();
}

void FUpdatePerceptionDataStateTreeAITask::ClearCachedInstanceData() const
{
	WeakInstanceStorage = nullptr;
	CachedOwner = nullptr;
}

void FUpdatePerceptionDataStateTreeAITask::OnTargetPerceptionUpdated(AActor* Actor, const FAIStimulus& Stimulus) const
{
	const TSharedPtr<FStateTreeInstanceStorage> InstanceStorage = WeakInstanceStorage.Pin();

	if (!ensureAlways(InstanceStorage.IsValid()))
	{
		return;
	}

	if (Stimulus.WasSuccessfullySensed())
	{
		InstanceStorage->GetMutableEventQueue().SendEvent(CachedOwner,
			ProjectTyrantGameplayTags::StateTree_Event_AI_FoundPlayer);
	}
	else
	{
		InstanceStorage->GetMutableEventQueue().SendEvent(CachedOwner,
			ProjectTyrantGameplayTags::StateTree_Event_AI_LostPlayer);
	}
}