// Vladislav Semchuk, 2025

#include "StateTree/StateTreeTasks/StateTreeAITasks/FindNextPointToInvestigateStateTreeAITask.h"

#include "AIController.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"

FFindNextPointToInvestigateStateTreeAITask::FFindNextPointToInvestigateStateTreeAITask()
{
	bShouldCallTick = false;
}

EStateTreeRunStatus FFindNextPointToInvestigateStateTreeAITask::EnterState(FStateTreeExecutionContext& Context,
	const FStateTreeTransitionResult& Transition) const
{
	const FInstanceDataType& InstanceData = Context.GetInstanceData(*this);

	const EStateTreeRunStatus PositiveReturnStatus = InstanceData.bRunTaskForever ?
		EStateTreeRunStatus::Running : EStateTreeRunStatus::Succeeded;

	const TArray<FVector>& Points = *InstanceData.PointsRef.GetMutablePtr<TArray<FVector>>(Context);

	// Make sure the Points array is not empty
	if (Points.IsEmpty())
	{
		return EStateTreeRunStatus::Failed;
	}

	TArray<FVector>& InOutInvestigatedPoints = *InstanceData.InOutInvestigatedPointsRef.GetMutablePtr<TArray<FVector>>(
		Context);

#if DO_ENSURE
	// Make sure the InOutInvestigatedPoints array is valid
	if (!ValidateInvestigatedPoints(Points, InOutInvestigatedPoints))
	{
		return EStateTreeRunStatus::Failed;
	}
#endif

	// If all points are already investigated, clear the InOutInvestigatedPoints array
	if (InOutInvestigatedPoints.Num() >= Points.Num())
	{
		InOutInvestigatedPoints.Empty();
	}

	TArray<FVector> PointsThatCouldBeInvestigated;
	GetPointsThatCanBeInvestigated(Points, InOutInvestigatedPoints, PointsThatCouldBeInvestigated);

	TMap<UNavigationPath*, FVector> PointsPaths;
	PointsPaths.Reserve(PointsThatCouldBeInvestigated.Num());

	const UNavigationSystemV1* NavigationSystem = UNavigationSystemV1::GetNavigationSystem(InstanceData.OwnerActor);

	if (!ensureAlways(IsValid(NavigationSystem)))
	{
		return EStateTreeRunStatus::Failed;
	}

	for (const FVector& PointThatCanBeInvestigated : PointsThatCouldBeInvestigated)
	{
		UNavigationPath* Path = NavigationSystem->FindPathToLocationSynchronously(InstanceData.OwnerActor, 
			InstanceData.OwnerActor->GetActorLocation(), PointThatCanBeInvestigated,
			InstanceData.OwnerActor);

		if (!ensureAlways(IsValid(Path)))
		{
			continue;
		}

		constexpr uint8 MinPathPoints = 2;

		// Make sure the path isn't too short before adding it to the map
		if (Path->PathPoints.Num() > MinPathPoints)
		{
			PointsPaths.Add(Path, PointThatCanBeInvestigated);
		}
		// If it is too short, then an AI actor is already at the point, so we can skip it and mark it as investigated
		else
		{
			InOutInvestigatedPoints.Add(PointThatCanBeInvestigated);
		}
	}

	TArray<UNavigationPath*> Paths;
	PointsPaths.GetKeys(Paths);

	/**
	 * We want to make sure the AI first investigates the points that were in his view cone ange before the first point
	 * was found, and only then investigates the other points.
	 */
	FVector& InOutAILocationBeforeFirstPoint = *InstanceData.InOutAILocationBeforeFirstPoint.GetMutablePtr(Context);
	FVector& InOutAIDirectionBeforeFirstPoint = *InstanceData.InOutAIDirectionBeforeFirstPoint.GetMutablePtr(
		Context);

	// Override AI's location and direction if it's the first point to find
	if (InOutInvestigatedPoints.IsEmpty())
	{
		InOutAILocationBeforeFirstPoint = InstanceData.OwnerActor->GetActorLocation();
		InOutAIDirectionBeforeFirstPoint = InstanceData.AIController->GetControlRotation().Vector();
	}

	TArray<UNavigationPath*> PreferredPaths;
	TArray<UNavigationPath*> NotPreferredPaths;
	FindPreferredPaths(Paths, InOutAILocationBeforeFirstPoint, InOutAIDirectionBeforeFirstPoint,
		InstanceData.PreferredFirstPointPathViewConeAngle, PreferredPaths, NotPreferredPaths);

	// First, try to find the shortest path in the preferred paths
	const UNavigationPath* PathToTheNextPointToInvestigate = FindShortestPath(PreferredPaths);

	// If we didn't find any, try to find the shortest path in the not preferred paths
	if (!PathToTheNextPointToInvestigate)
	{
		PathToTheNextPointToInvestigate = FindShortestPath(NotPreferredPaths);
	}

	// Fail if we didn't find any path to the next point to investigate
	if (!PathToTheNextPointToInvestigate)
	{
		return EStateTreeRunStatus::Failed;
	}

	FVector& OutNextPointToInvestigate = *InstanceData.OutNextPointToInvestigateRef.GetMutablePtr(Context);

	// Return the point related to the found path and remember it as investigated
	OutNextPointToInvestigate = PointsPaths.FindChecked(PathToTheNextPointToInvestigate);
	InOutInvestigatedPoints.Add(OutNextPointToInvestigate);

	return PositiveReturnStatus;
}

#if DO_ENSURE
bool FFindNextPointToInvestigateStateTreeAITask::ValidateInvestigatedPoints(const TArray<FVector>& Points,
	const TArray<FVector>& InvestigatedPoints)
{
	bool bInvestigatedPointsAreValid = true;

	// Iterate through all InvestigatedPoints and check if they are in the Points array
	for (const FVector& InvestigatedPoint : InvestigatedPoints)
	{
		bool bFoundEqualPoint = false;

		// Find any Point that equals the InvestigatedPoint
		for (const FVector& Point : Points)
		{
			if (InvestigatedPoint.Equals(Point))
			{
				bFoundEqualPoint = true;

				// Break the internal loop since we found an InvestigatedPoint in a Points array
				break;
			}
		}

		// Trigger an ensure if we didn't find the InvestigatedPoint in the Points array and mark the array as invalid
		if (!bFoundEqualPoint)
		{
#if DO_ENSURE
			ensureAlwaysMsgf(true, TEXT("Investigated point %s is not in the Points array!"),
				*InvestigatedPoint.ToString());
#endif

			bInvestigatedPointsAreValid = false;
		}
	}

	return bInvestigatedPointsAreValid;
}
#endif

void FFindNextPointToInvestigateStateTreeAITask::GetPointsThatCanBeInvestigated(const TArray<FVector>& Points,
	const TArray<FVector>& InvestigatedPoints, TArray<FVector>& OutPointsThatCanBeInvestigated)
{
	// There is nothing to filter if an InvestigatedPoints array is empty
	if (InvestigatedPoints.IsEmpty())
	{
		OutPointsThatCanBeInvestigated = Points;

		return;
	}

	for (const FVector& Point : Points)
	{
		bool bAlreadyInvestigated = false;

		for (const FVector& InvestigatedPoint : InvestigatedPoints)
		{
			// If the Point is already investigated, skip it
			if (Point.Equals(InvestigatedPoint))
			{
				bAlreadyInvestigated = true;

				break;
			}
		}

		// If the Point is not already investigated, add it to the OutPointsThatCanBeInvestigated array
		if (!bAlreadyInvestigated)
		{
			OutPointsThatCanBeInvestigated.Add(Point);
		}
	}
}

void FFindNextPointToInvestigateStateTreeAITask::FindPreferredPaths(const TArray<UNavigationPath*>& Paths,
	const FVector& AILocation, const FVector& AIDirection, const float ViewConeAngle,
	TArray<UNavigationPath*>& OutPreferredPaths, TArray<UNavigationPath*>& OutNotPreferredPaths)
{
	for (UNavigationPath* Path : Paths)
	{
		if (IsPathInViewCone(Path, AILocation, AIDirection, ViewConeAngle))
		{
			OutPreferredPaths.Add(Path);
		}
		else
		{
			OutNotPreferredPaths.Add(Path);
		}
	}
}

bool FFindNextPointToInvestigateStateTreeAITask::IsPathInViewCone(const UNavigationPath* Path,
	const FVector& AILocation, const FVector& AIControlDirection, const float ViewConeAngle)
{
#if DO_CHECK
	check(IsValid(Path));
	check(Path->PathPoints.Num() > 2);
#endif

	/**
	 * Get the direction of the path start point by subtracting the AI location from the second point of the path (the
	 * first one could be equal to the AI location).
	 */
	const FVector PathStartDirection = (Path->PathPoints[1] - AILocation).GetSafeNormal();

	const float DirectionsDotProduct = FVector::DotProduct(AIControlDirection, PathStartDirection);
	const float CosHalfFOV = FMath::Cos(FMath::DegreesToRadians(ViewConeAngle / 2));

	return DirectionsDotProduct >= CosHalfFOV;
}

UNavigationPath* FFindNextPointToInvestigateStateTreeAITask::FindShortestPath(const TArray<UNavigationPath*>& Paths)
{
	double ShortestPathLength = TNumericLimits<double>::Max();
	UNavigationPath* ShortestPath = nullptr;

	for (UNavigationPath* Path : Paths)
	{
#if DO_CHECK
		check(IsValid(Path));
#endif

		if (Path->GetPathLength() < ShortestPathLength)
		{
			ShortestPathLength = Path->GetPathLength();
			ShortestPath = Path;
		}
	}

	return ShortestPath;
}