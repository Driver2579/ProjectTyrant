// Vladislav Semchuk, 2025

#include "StateTree/StateTreeTasks/StateTreeAITasks/IsNearAnActorDuringSpecifiedTimeStateTreeAITask.h"

#include "ProjectTyrantGameplayTags.h"
#include "StateTreeExecutionContext.h"

EStateTreeRunStatus FIsNearAnActorDuringSpecifiedTimeStateTreeAITask::EnterState(FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition) const
{
	FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

	Context.GetWorld()->GetTimerManager().SetTimer(InstanceData.TimerHandle, InstanceData.TaskDuration,
		false);

	return EStateTreeRunStatus::Running;
}

EStateTreeRunStatus FIsNearAnActorDuringSpecifiedTimeStateTreeAITask::Tick(FStateTreeExecutionContext& Context,
	const float DeltaTime) const
{
	FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

	FTimerManager& TimerManager = Context.GetWorld()->GetTimerManager();

	if (!TimerManager.TimerExists(InstanceData.TimerHandle))
	{
		return EStateTreeRunStatus::Succeeded;
	}

	if (!TimerManager.IsTimerActive(InstanceData.TimerHandle))
	{
		return EStateTreeRunStatus::Running;
	}

	if (!ensureAlways(InstanceData.TargetActor))
	{
		if (TimerManager.TimerExists(InstanceData.TimerHandle))
		{
			TimerManager.ClearTimer(InstanceData.TimerHandle);
		}

		return EStateTreeRunStatus::Failed;
	}

	FVector OwnerActorLocation = InstanceData.OwnerActor->GetActorLocation();
	FVector TargetActorLocation = InstanceData.TargetActor->GetActorLocation();

	// Don't take Z axis into account
	OwnerActorLocation.Z = 0;
	TargetActorLocation.Z = 0;

	float Distance = FVector::Distance(OwnerActorLocation, TargetActorLocation);

	/**
	 * There is no need to check for radiuses if the distance between the two actors is less or equal to the acceptable
	 * radius. The radiuses are only used to decrease the distance value.
	 */
	if (Distance <= InstanceData.AcceptableRadius)
	{
		SetOutputValue(Context, InstanceData, true);

		return EStateTreeRunStatus::Running;
	}

	// Subtract the radius of the OwnerActor from the distance if needed
	if (InstanceData.bTestIncludesAgentRadius)
	{
		Distance -= GetActorCollisionRadius(InstanceData.OwnerActor);
	}

	// Subtract the radius of the TargetActor from the distance if needed
	if (InstanceData.bTestIncludesTargetRadius)
	{
		Distance -= GetActorCollisionRadius(InstanceData.TargetActor);
	}

	// Set the output value based on the final calculated distance
	SetOutputValue(Context, InstanceData, Distance <= InstanceData.AcceptableRadius);

	return EStateTreeRunStatus::Running;
}

float FIsNearAnActorDuringSpecifiedTimeStateTreeAITask::GetActorCollisionRadius(const AActor* Actor)
{
#if DO_CHECK
	check(IsValid(Actor));
#endif

	float CollisionRadius;
	float CollisionHalfHeight;
	Actor->GetComponentsBoundingCylinder(CollisionRadius, CollisionHalfHeight);

	return CollisionRadius;
}

void FIsNearAnActorDuringSpecifiedTimeStateTreeAITask::SetOutputValue(const FStateTreeExecutionContext& Context,
	FInstanceDataType& InstanceData, const bool bNewValue)
{
	// Send an "IsNotNearAnymore" event if actors used to be near each other but are not anymore
	if (!bNewValue && bNewValue != InstanceData.bOutIsNearAnActor)
	{
		Context.SendEvent(ProjectTyrantGameplayTags::StateTree_Event_AI_IsNotNearAnymore);
	}

	InstanceData.bOutIsNearAnActor = bNewValue;
}