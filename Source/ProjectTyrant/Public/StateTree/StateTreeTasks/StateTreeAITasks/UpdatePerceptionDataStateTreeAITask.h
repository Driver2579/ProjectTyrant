﻿// Vladislav Semchuk, 2025

#pragma once

#include "CoreMinimal.h"
#include "StateTreeTaskBase.h"
#include "UpdatePerceptionDataStateTreeAITask.generated.h"

USTRUCT()
struct FUpdatePerceptionDataStateTreeAITaskInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Context")
	TObjectPtr<class AAIController> AIController;

	FDelegateHandle OnTargetPerceptionUpdatedDelegateHandle;
};

// AI task that sends events when the perception data is updated
USTRUCT(meta=(DisplayName="Update Perception Data"))
struct FUpdatePerceptionDataStateTreeAITask : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	FUpdatePerceptionDataStateTreeAITask();

	using FInstanceDataType = FUpdatePerceptionDataStateTreeAITaskInstanceData;

	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context,
		const FStateTreeTransitionResult& Transition) const override;

	virtual void ExitState(FStateTreeExecutionContext& Context,
		const FStateTreeTransitionResult& Transition) const override;

protected:
	virtual void OnTargetPerceptionUpdated(AActor* Actor, const struct FAIStimulus& Stimulus) const;

private:
	void SetCachedInstanceDataFromContext(const FStateTreeExecutionContext& Context) const;
	void ClearCachedInstanceData() const;

	/**
	 * Unfortunately, we need to store the instance storage here to pass it to the callback function and make it mutable
	 * because overriden functions are const. We need it to be able to send an event. UStateTreeNodeBlueprintBase does
	 * the same thing.
	 */
	mutable TWeakPtr<struct FStateTreeInstanceStorage> WeakInstanceStorage;

	// We need it for the same reason as a WeakInstanceStorage
	UPROPERTY(Transient)
	mutable TObjectPtr<UObject> CachedOwner = nullptr;
};