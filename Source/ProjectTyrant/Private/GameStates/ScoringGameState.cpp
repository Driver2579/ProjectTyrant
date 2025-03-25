// Vladislav Semchuk, 2025

#include "GameStates/ScoringGameState.h"

AScoringGameState::AScoringGameState()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AScoringGameState::BeginPlay()
{
	Super::BeginPlay();

	if (CurrentScore >= TargetScore)
	{
		OnTargetScoreReached.Broadcast();
	}
}

void AScoringGameState::AddScore(const uint16 ScoreToAdd)
{
	const uint16 OldScore = CurrentScore;
	CurrentScore = FMath::Clamp<uint16>(CurrentScore + ScoreToAdd, 0, TargetScore);

	if (OldScore != CurrentScore)
	{
		OnCurrentScoreChanged.Broadcast(CurrentScore);
	}

	if (CurrentScore >= TargetScore)
	{
		OnTargetScoreReached.Broadcast();
	}
}

void AScoringGameState::CallOrRegister_OnTargetScoreReached(const FSimpleMulticastDelegate::FDelegate&& Delegate)
{
	if (CurrentScore >= TargetScore)
	{
		Delegate.ExecuteIfBound();
	}
	else
	{
		OnTargetScoreReached.Add(Delegate);
	}
}