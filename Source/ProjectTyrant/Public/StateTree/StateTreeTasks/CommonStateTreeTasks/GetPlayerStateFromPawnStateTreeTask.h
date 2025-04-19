// Vladislav Semchuk, 2025

#pragma once

#include "CoreMinimal.h"
#include "StateTreeTaskBase.h"
#include "GetPlayerStateFromPawnStateTreeTask.generated.h"

USTRUCT()
struct FGetPlayerStateFromPawnStateTreeTaskInstanceData
{
	GENERATED_BODY()

	/**
	 * If true, the task will return the "Running" status. If false, the task will return the "Succeeded" status.
	 * 
	 * Note: If the task fails, it will always return the "Failed" status regardless of this property.
	 */
	UPROPERTY(EditAnywhere, Category="Parameter")
	bool bRunTaskForever = false;

	// Pawn to get the PlayerState from
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<AActor> Pawn;

	UPROPERTY(Transient, VisibleAnywhere, Category="Output")
	TObjectPtr<APlayerState> OutPlayerState; 
};

USTRUCT(meta=(DisplayName="Get PlayerState From Pawn"))
struct FGetPlayerStateFromPawnStateTreeTask : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	FGetPlayerStateFromPawnStateTreeTask();

	using FInstanceDataType = FGetPlayerStateFromPawnStateTreeTaskInstanceData;

	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context,
		const FStateTreeTransitionResult& Transition) const override;
};