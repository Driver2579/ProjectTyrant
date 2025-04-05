// Vladislav Semchuk, 2025

#pragma once

#include "CoreMinimal.h"
#include "StateTreeTaskBase.h"
#include "GetActorLocationStateTreeTask.generated.h"

USTRUCT()
struct FGetActorLocationStateTreeTaskInstanceData
{
	GENERATED_BODY()

	/**
	 * If true, the task will return the "Running" status. If false, the task will return the "Succeeded" status.
	 * 
	 * Note: If the task fails, it will always return the "Failed" status regardless of this property.
	 */
	UPROPERTY(EditAnywhere, Category="Parameter")
	bool bRunTaskForever = false;

	// Actor to get the location of
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<AActor> Actor;

	UPROPERTY(Transient, VisibleAnywhere, Category="Output")
	FVector OutActorLocation;
};

USTRUCT(meta=(DisplayName="Get Actor Location"))
struct FGetActorLocationStateTreeTask : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	FGetActorLocationStateTreeTask();

	using FInstanceDataType = FGetActorLocationStateTreeTaskInstanceData;

	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context,
		const FStateTreeTransitionResult& Transition) const override;
};