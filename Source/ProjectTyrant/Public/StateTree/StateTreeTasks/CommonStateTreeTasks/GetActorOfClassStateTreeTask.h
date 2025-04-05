// Vladislav Semchuk, 2025

#pragma once

#include "CoreMinimal.h"
#include "StateTreeTaskBase.h"
#include "StateTreePropertyRef.h"
#include "GetActorOfClassStateTreeTask.generated.h"

USTRUCT()
struct FGetActorOfClassStateTreeTaskInstanceData
{
	GENERATED_BODY()

	/**
	 * If true, the task will return the "Running" status. If false, the task will return the "Succeeded" status.
	 * 
	 * Note: If the task fails, it will always return the "Failed" status regardless of this property.
	 */
	UPROPERTY(EditAnywhere, Category="Parameter")
	bool bRunTaskForever = false;

	UPROPERTY(EditAnywhere, Category="Parameter")
	TSubclassOf<AActor> ActorClass;

	UPROPERTY(EditAnywhere, Category="Input", DisplayName="Out Actor")
	TStateTreePropertyRef<AActor*> OutActorRef;
};

/**
 * A task that gets the first actor of a specified class in the world and stores it in an output property reference.\n
 * \n
 * Note: You cannot pass a child class of an Actor class to this task. The task will only accept the base class (Actor).
 */
USTRUCT(meta=(DisplayName="Get Actor of Class"))
struct FGetActorOfClassStateTreeTask : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	FGetActorOfClassStateTreeTask();

	using FInstanceDataType = FGetActorOfClassStateTreeTaskInstanceData;

	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context,
		const FStateTreeTransitionResult& Transition) const override;
};