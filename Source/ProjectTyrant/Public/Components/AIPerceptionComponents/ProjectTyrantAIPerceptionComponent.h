// Vladislav Semchuk, 2025

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "ProjectTyrantAIPerceptionComponent.generated.h"

UCLASS(ClassGroup=(AI), meta=(BlueprintSpawnableComponent))
class PROJECTTYRANT_API UProjectTyrantAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()

public:
	DECLARE_MULTICAST_DELEGATE_OneParam(FPerceptionUpdatedDelegateStatic, const TArray<AActor*>& UpdatedActors);

	DECLARE_MULTICAST_DELEGATE_TwoParams(FActorPerceptionUpdatedDelegateStatic, AActor* Actor,
		const FAIStimulus& Stimulus);

	DECLARE_MULTICAST_DELEGATE_OneParam(FActorPerceptionForgetUpdatedDelegateStatic, AActor* Actor);

	DECLARE_MULTICAST_DELEGATE_OneParam(FActorPerceptionInfoUpdatedDelegateStatic,
		const FActorPerceptionUpdateInfo& UpdateInfo);

	// Static version of OnPerceptionUpdated delegate
	FPerceptionUpdatedDelegateStatic OnPerceptionUpdatedStatic;

	// Static version of OnTargetPerceptionUpdated delegate
	FActorPerceptionUpdatedDelegateStatic OnTargetPerceptionUpdatedStatic;

	// Static version of OnTargetPerceptionForgotten delegate
	FActorPerceptionForgetUpdatedDelegateStatic OnTargetPerceptionForgottenStatic;

	// Static version of OnTargetPerceptionInfoUpdated delegate
	FActorPerceptionInfoUpdatedDelegateStatic OnTargetPerceptionInfoUpdatedStatic;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnPerceptionUpdatedCallback(const TArray<AActor*>& UpdatedActors);

	UFUNCTION()
	void OnTargetPerceptionUpdatedCallback(AActor* Actor, FAIStimulus Stimulus);

	UFUNCTION()
	void OnTargetPerceptionForgottenCallback(AActor* Actor);

	UFUNCTION()
	void OnTargetPerceptionInfoUpdatedCallback(const FActorPerceptionUpdateInfo& UpdateInfo);
};