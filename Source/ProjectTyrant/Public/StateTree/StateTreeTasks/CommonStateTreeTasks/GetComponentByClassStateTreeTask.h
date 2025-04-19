// Vladislav Semchuk, 2025

#pragma once

#include "CoreMinimal.h"
#include "StateTreeTaskBase.h"
#include "GetComponentByClassStateTreeTask.generated.h"

USTRUCT()
struct FGetComponentByClassStateTreeTaskInstanceData
{
	GENERATED_BODY()

	/**
	 * If true, the task will return the "Running" status. If false, the task will return the "Succeeded" status.
	 * 
	 * Note: If the task fails, it will always return the "Failed" status regardless of this property.
	 */
	UPROPERTY(EditAnywhere, Category="Parameter")
	bool bRunTaskForever = false;

	// Actor to get the component from
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<AActor> Actor;

	UPROPERTY(EditAnywhere, Category="Parameter")
	TSubclassOf<UActorComponent> ComponentClass;

	UPROPERTY(Transient, VisibleAnywhere, Category="Output")
	TObjectPtr<UActorComponent> OutComponent;
};

USTRUCT(meta=(DisplayName="Get Component by Class"))
struct FGetComponentByClassStateTreeTask : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	FGetComponentByClassStateTreeTask();

	using FInstanceDataType = FGetComponentByClassStateTreeTaskInstanceData;

	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context,
		const FStateTreeTransitionResult& Transition) const override;
};