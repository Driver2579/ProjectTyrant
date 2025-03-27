// Vladislav Semchuk, 2025

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreWidget.generated.h"

class UTextBlock;

// The widget that shows the current score and the target score from the AScoringGameState
UCLASS()
class PROJECTTYRANT_API UScoreWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(Transient, meta=(BindWidget))
	TObjectPtr<UTextBlock> CurrentScore;

	UPROPERTY(Transient, meta=(BindWidget))
	TObjectPtr<UTextBlock> TargetScore;

	void OnCurrentScoreChanged(const uint16 NewCurrentScore) const;
};