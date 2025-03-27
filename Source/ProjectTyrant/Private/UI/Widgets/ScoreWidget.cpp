// Vladislav Semchuk, 2025

#include "UI/Widgets/ScoreWidget.h"

#include "Blueprint/WidgetTree.h"
#include "Components/TextBlock.h"
#include "GameStates/ScoringGameState.h"

void UScoreWidget::NativeConstruct()
{
	Super::NativeConstruct();

	AScoringGameState* ScoringGameState = GetWorld()->GetGameState<AScoringGameState>();

	if (!IsValid(ScoringGameState))
	{
		return;
	}

	if (CurrentScoreText)
	{
		CurrentScoreText->SetText(FText::AsNumber(ScoringGameState->GetCurrentScore()));
	}

	if (TargetScoreText)
	{
		TargetScoreText->SetText(FText::AsNumber(ScoringGameState->GetTargetScore()));
	}

	ScoringGameState->OnCurrentScoreChanged.AddUObject(this, &ThisClass::OnCurrentScoreChanged);
}

void UScoreWidget::OnCurrentScoreChanged(const uint16 CurrentScore) const
{
	if (CurrentScoreText)
	{
		CurrentScoreText->SetText(FText::AsNumber(CurrentScore));
	}
}