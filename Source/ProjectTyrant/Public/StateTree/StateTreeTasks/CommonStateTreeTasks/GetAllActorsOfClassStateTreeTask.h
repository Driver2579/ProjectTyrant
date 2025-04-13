// Vladislav Semchuk, 2025

#pragma once

#include "CoreMinimal.h"
#include "StateTreeTaskBase.h"
#include "StateTreePropertyRef.h"
#include "GetAllActorsOfClassStateTreeTask.generated.h"

USTRUCT()
struct FGetAllActorsOfClassStateTreeTaskInstanceData
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

	UPROPERTY(EditAnywhere, Category="Output")
	TArray<AActor*> OutActors;
};

/**
 * A task that gets all actors of a specified class in the world and stores them in an output property reference.
 * 
 * Note: You cannot pass child classes of an Actor class to this task. The task will only accept the base class
 * (Actors).
 */
USTRUCT(meta=(DisplayName="Get All Actors of Class"))
struct FGetAllActorsOfClassStateTreeTask : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	FGetAllActorsOfClassStateTreeTask();

	using FInstanceDataType = FGetAllActorsOfClassStateTreeTaskInstanceData;

	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context,
		const FStateTreeTransitionResult& Transition) const override;
};