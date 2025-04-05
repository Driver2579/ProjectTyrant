// Vladislav Semchuk, 2025

#pragma once

#include "CoreMinimal.h"
#include "StateTreeTaskBase.h"
#include "StateTreePropertyRef.h"
#include "LoseGameStateTreeTask.generated.h"

USTRUCT()
struct FLoseGameStateTreeTaskInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<AActor> PlayerPawn;
};

// A gameplay task that calls the "Lose" function in the GameMode and returns the "Succeeded" status
USTRUCT(meta=(DisplayName=""))
struct FLoseGameStateTreeTask : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	FLoseGameStateTreeTask();

	using FInstanceDataType = FLoseGameStateTreeTaskInstanceData;

	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context,
		const FStateTreeTransitionResult& Transition) const override;
};