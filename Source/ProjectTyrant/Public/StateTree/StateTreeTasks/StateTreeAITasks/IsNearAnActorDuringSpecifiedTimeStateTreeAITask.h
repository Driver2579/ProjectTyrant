// Vladislav Semchuk, 2025

#pragma once

#include "CoreMinimal.h"
#include "StateTreeTaskBase.h"
#include "StateTreePropertyRef.h"
#include "IsNearAnActorDuringSpecifiedTimeStateTreeAITask.generated.h"

USTRUCT()
struct FIsNearAnActorDuringSpecifiedTimeStateTreeAITaskInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Context")
	TObjectPtr<AActor> OwnerActor;

	// Actor to check the distance to
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<AActor> TargetActor;

	// How long this task will update the state
	UPROPERTY(EditDefaultsOnly, Category="Parameter", meta=(ClampMin=0.1))
	float TaskDuration = 1;

	// Acceptable distance between the two actors to consider them near each other
	UPROPERTY(EditAnywhere, Category="Parameter", meta=(ClampMin=0))
	float AcceptableRadius = 5;

	// If true, the radius of AI's capsule will be added to a threshold between AI and target actor in the distance test
	UPROPERTY(EditAnywhere, Category="Parameter")
	bool bTestIncludesAgentRadius = true;

	/**
	 * If true, the radius of target actor's capsule will be added to a threshold between AI and target actor in the
	 * distance test.
	 */
	UPROPERTY(EditAnywhere, Category="Parameter")
	bool bTestIncludesTargetRadius = true;

	UPROPERTY(Transient, VisibleAnywhere, Category="Output", DisplayName="Out Is Near an Actor")
	bool bOutIsNearAnActor;

	FTimerHandle TimerHandle;
};

/**
 * This task checks if the AI is near a target actor for a specified amount of time, updating the output value every
 * tick while this task is running. The task succeeds once the specified time has passed. If an AI was near the target
 * actor in the previous tick but isn't in the current tick, then the "StateTree.Event.AI.IsNotNearAnymore" event will
 * be sent.
 */
USTRUCT(meta=(DisplayName="Is Near an Actor During Specified Time"))
struct FIsNearAnActorDuringSpecifiedTimeStateTreeAITask : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	using FInstanceDataType = FIsNearAnActorDuringSpecifiedTimeStateTreeAITaskInstanceData;

	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context,
		const FStateTreeTransitionResult& Transition) const override;

	virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;

private:
	static float GetActorCollisionRadius(const AActor* Actor);

	static void SetOutputValue(const FStateTreeExecutionContext& Context, FInstanceDataType& InstanceData,
		const bool bNewValue);
};