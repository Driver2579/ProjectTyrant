// Vladislav Semchuk, 2025

#pragma once

#include "CoreMinimal.h"
#include "StateTreeTaskBase.h"
#include "PlayLoopedMusicStateTreeTask.generated.h"

USTRUCT()
struct FPlayLoopedMusicStateTreeTaskInstanceData
{
	GENERATED_BODY()

	/**
	 * If true, the task will return the "Running" status. If false, the task will return the "Succeeded" status.
	 * 
	 * Note: If the task fails, it will always return the "Failed" status regardless of this property.
	 */
	UPROPERTY(EditAnywhere, Category="Parameter")
	bool bRunTaskForever = false;

	// Component to play the music on. MUST be a LoopedMusicManagerComponent!
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UActorComponent> LoopedMusicManagerComponent;
};

// Calls PlayMusic method on the given LoopedMusicManagerComponent
USTRUCT(meta=(DisplayName="Play Looped Music"))
struct FPlayLoopedMusicStateTreeTask : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	FPlayLoopedMusicStateTreeTask();

	using FInstanceDataType = FPlayLoopedMusicStateTreeTaskInstanceData;

	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context,
		const FStateTreeTransitionResult& Transition) const override;
};