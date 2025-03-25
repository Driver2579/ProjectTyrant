// Vladislav Semchuk, 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ScoringGameState.generated.h"

// GameState class that contains the current score and target score for the game
UCLASS()
class PROJECTTYRANT_API AScoringGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	AScoringGameState();

	virtual void BeginPlay() override;

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnCurrentScoreChangedDelegate, uint16 CurrentScore);

	FOnCurrentScoreChangedDelegate OnCurrentScoreChanged;

	uint16 GetCurrentScore() const { return CurrentScore; }
	void AddScore(const uint16 ScoreToAdd = 1);

	uint16 GetTargetScore() const { return TargetScore; }

	void CallOrRegister_OnTargetScoreReached(const FSimpleMulticastDelegate::FDelegate&& Delegate);

private:
	uint16 CurrentScore = 0;

	UPROPERTY(EditDefaultsOnly, Category="Scoring")
	uint16 TargetScore = 0;

	FSimpleMulticastDelegate OnTargetScoreReached;
};