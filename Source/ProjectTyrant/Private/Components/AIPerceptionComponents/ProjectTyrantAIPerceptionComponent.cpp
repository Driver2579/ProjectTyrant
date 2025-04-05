// Vladislav Semchuk, 2025

#include "Components/AIPerceptionComponents/ProjectTyrantAIPerceptionComponent.h"

void UProjectTyrantAIPerceptionComponent::BeginPlay()
{
	Super::BeginPlay();

	OnPerceptionUpdated.AddDynamic(this, &ThisClass::OnPerceptionUpdatedCallback);
	OnTargetPerceptionUpdated.AddDynamic(this, &ThisClass::OnTargetPerceptionUpdatedCallback);
	OnTargetPerceptionForgotten.AddDynamic(this, &ThisClass::OnTargetPerceptionForgottenCallback);
	OnTargetPerceptionInfoUpdated.AddDynamic(this, &ThisClass::OnTargetPerceptionInfoUpdatedCallback);
}

// ReSharper disable CppMemberFunctionMayBeConst
void UProjectTyrantAIPerceptionComponent::OnPerceptionUpdatedCallback(const TArray<AActor*>& UpdatedActors)
{
	OnPerceptionUpdatedStatic.Broadcast(UpdatedActors);
}

// ReSharper disable once CppPassValueParameterByConstReference
void UProjectTyrantAIPerceptionComponent::OnTargetPerceptionUpdatedCallback(AActor* Actor, FAIStimulus Stimulus)
{
	OnTargetPerceptionUpdatedStatic.Broadcast(Actor, Stimulus);
}

void UProjectTyrantAIPerceptionComponent::OnTargetPerceptionForgottenCallback(AActor* Actor)
{
	OnTargetPerceptionForgottenStatic.Broadcast(Actor);
}

void UProjectTyrantAIPerceptionComponent::OnTargetPerceptionInfoUpdatedCallback(
	const FActorPerceptionUpdateInfo& UpdateInfo)
{
	OnTargetPerceptionInfoUpdatedStatic.Broadcast(UpdateInfo);
}
// ReSharper restore CppMemberFunctionMayBeConst