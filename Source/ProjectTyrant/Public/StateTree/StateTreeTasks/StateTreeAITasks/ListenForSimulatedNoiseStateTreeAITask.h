// Vladislav Semchuk, 2025

#pragma once

#include "CoreMinimal.h"
#include "StateTreeTaskBase.h"
#include "ListenForSimulatedNoiseStateTreeAITask.generated.h"

USTRUCT()
struct FListenForSimulatedNoiseStateTreeAITaskInstanceData
{
	GENERATED_BODY()

	FDelegateHandle OnPlayerMadeNoiseDelegateHandle;
};

USTRUCT(meta=(DisplayName="Listen for Simulated Noise"))
struct FListenForSimulatedNoiseStateTreeAITask : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	FListenForSimulatedNoiseStateTreeAITask();

	using FInstanceDataType = FListenForSimulatedNoiseStateTreeAITaskInstanceData;

	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context,
		const FStateTreeTransitionResult& Transition) const override;

	virtual void ExitState(FStateTreeExecutionContext& Context,
		const FStateTreeTransitionResult& Transition) const override;

protected:
	virtual void OnPlayerMadeNoise() const;

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