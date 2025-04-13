// Vladislav Semchuk, 2025

#pragma once

#include "CoreMinimal.h"
#include "StateTreeTaskBase.h"
#include "StateTreePropertyRef.h"
#include "FindNextPointToInvestigateStateTreeAITask.generated.h"

class UNavigationPath;

USTRUCT()
struct FFindNextPointToInvestigateStateTreeAITaskInstanceData
{
	GENERATED_BODY()

	/**
	 * If true, the task will return the "Running" status. If false, the task will return the "Succeeded" status.
	 * 
	 * Note: If the task fails, it will always return the "Failed" status regardless of this property.
	 */
	UPROPERTY(EditAnywhere, Category="Parameter")
	bool bRunTaskForever = false;

	UPROPERTY(EditAnywhere, Category="Context")
	TObjectPtr<AActor> OwnerActor;

	UPROPERTY(EditAnywhere, Category="Context")
	TObjectPtr<class AAIController> AIController;

	// All points AI can investigate
	UPROPERTY(EditAnywhere, Category="Input", DisplayName="Points",
		meta=(RefType="/Script/CoreUObject.Vector", IsRefToArray))
	FStateTreePropertyRef PointsRef;

	/**
	 * All points AI has already investigated. Found point will be added to this array by the end of this task. If this
	 * array already contains all points from the "Points" array, then it's going to be cleared first.
	 */
	UPROPERTY(EditAnywhere, Category="Input", DisplayName="InOut Investigated Points",
		meta=(RefType="/Script/CoreUObject.Vector", IsRefToArray))
	FStateTreePropertyRef InOutInvestigatedPointsRef;

	UPROPERTY(EditAnywhere, Category="Input", DisplayName="InOut AI Location Before First Point")
	TStateTreePropertyRef<FVector> InOutAILocationBeforeFirstPoint;

	UPROPERTY(EditAnywhere, Category="Input", DisplayName="InOut AI Direction Before First Point")
	TStateTreePropertyRef<FVector> InOutAIDirectionBeforeFirstPoint;

	/**
	 * The path to points within the specified view cone of the AI's direction and location (that are cached before the
	 * first point is found) will be preferred over the other points even if their paths are shorter.
	 */
	UPROPERTY(EditAnywhere, Category="Parameter", meta=(ClampMin=0, ClampMax=360))
	float PreferredFirstPointPathViewConeAngle = 90;

	UPROPERTY(EditAnywhere, Category="Input", DisplayName="Out Next Point to Investigate")
	TStateTreePropertyRef<FVector> OutNextPointToInvestigateRef;
};

/**
 * This task finds the next point for the AI to investigate by finding the one that has the shortest path to it. An
 * algorithm also makes sure that the AI first investigates the points that were in his view cone before the first point
 * was found, and only then investigates the other points.
 */
USTRUCT(meta=(DisplayName="Find Next Point to Investigate"))
struct FFindNextPointToInvestigateStateTreeAITask : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	FFindNextPointToInvestigateStateTreeAITask();

	using FInstanceDataType = FFindNextPointToInvestigateStateTreeAITaskInstanceData;

	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context,
		const FStateTreeTransitionResult& Transition) const override;

private:
#if DO_ENSURE
	// Ensures that the InvestigatedPoints array doesn't contain any point outside the Points array
	static bool ValidateInvestigatedPoints(const TArray<FVector>& Points, const TArray<FVector>& InvestigatedPoints);
#endif

	// Filters the Points array to only include points that are not in the InvestigatedPoints array
	static void GetPointsThatCanBeInvestigated(const TArray<FVector>& Points,
		const TArray<FVector>& InvestigatedPoints, TArray<FVector>& OutPointsThatCanBeInvestigated);

	static bool IsPathInViewCone(const UNavigationPath* Path, const FVector& AILocation,
		const FVector& AIControlDirection, const float ViewConeAngle);

	/**
	 * Finds the preferred paths based on the AI direction and the view cone angle. If the direction of the path's start
	 * is within the passed view cone angle of the AI direction, the path will be added to the preferred paths.
	 * Otherwise, it will be added to the not preferred paths.
	 */
	static void FindPreferredPaths(const TArray<UNavigationPath*>& Paths, const FVector& AILocation,
		const FVector& AIDirection, const float ViewConeAngle, TArray<UNavigationPath*>& OutPreferredPaths,
		TArray<UNavigationPath*>& OutNotPreferredPaths);

	static UNavigationPath* FindShortestPath(const TArray<UNavigationPath*>& Paths);
};