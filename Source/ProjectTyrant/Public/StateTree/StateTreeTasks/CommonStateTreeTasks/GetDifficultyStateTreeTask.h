// Vladislav Semchuk, 2025

#pragma once

#include "CoreMinimal.h"
#include "StateTreeTaskBase.h"
#include "StateTreePropertyRef.h"
#include "Common/Enums/Difficulty.h"
#include "GetDifficultyStateTreeTask.generated.h"

enum class EDifficulty : uint8;

USTRUCT()
struct FGetDifficultyStateTreeTaskInstanceData
{
	GENERATED_BODY()

	/**
	 * If true, the task will return the "Running" status. If false, the task will return the "Succeeded" status.
	 * 
	 * Note: If the task fails, it will always return the "Failed" status regardless of this property.
	 */
	UPROPERTY(EditAnywhere, Category="Parameter")
	bool bRunTaskForever = false;

	UPROPERTY(EditAnywhere, Category="Output")
	EDifficulty OutDifficulty = EDifficulty::None;
};

// Gets the difficulty from the GameInstance
USTRUCT(meta=(DisplayName="Get Difficulty"))
struct FGetDifficultyStateTreeTask : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	FGetDifficultyStateTreeTask();

	using FInstanceDataType = FGetDifficultyStateTreeTaskInstanceData;

	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context,
		const FStateTreeTransitionResult& Transition) const override;
};