// Vladislav Semchuk, 2025

#pragma once

#include "CoreMinimal.h"
#include "StateTreeTaskBase.h"
#include "StateTreePropertyRef.h"
#include "GetActorsLocationsStateTreeTask.generated.h"

USTRUCT()
struct FGetActorsLocationsStateTreeTaskInstanceData
{
	GENERATED_BODY()

	/**
	 * If true, the task will return the "Running" status. If false, the task will return the "Succeeded" status.
	 * 
	 * Note: If the task fails, it will always return the "Failed" status regardless of this property.
	 */
	UPROPERTY(EditAnywhere, Category="Parameter")
	bool bRunTaskForever = false;

	// Actors to get the locations of
	UPROPERTY(EditAnywhere, Category="Input")
	TArray<TObjectPtr<AActor>> Actors;

	UPROPERTY(EditAnywhere, Category="Output")
	TArray<FVector> OutActorsLocations;
};

// Translates an array of actors to an array of their locations
USTRUCT(meta=(DisplayName="Get Actors Locations"))
struct FGetActorsLocationsStateTreeTask : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	FGetActorsLocationsStateTreeTask();

	using FInstanceDataType = FGetActorsLocationsStateTreeTaskInstanceData;

	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context,
		const FStateTreeTransitionResult& Transition) const override;
};