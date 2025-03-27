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

	if (CurrentScore)
	{
		CurrentScore->SetText(FText::AsNumber(ScoringGameState->GetCurrentScore()));
	}

	if (TargetScore)
	{
		TargetScore->SetText(FText::AsNumber(ScoringGameState->GetTargetScore()));
	}

	ScoringGameState->OnCurrentScoreChanged.AddUObject(this, &ThisClass::OnCurrentScoreChanged);
}

void UScoreWidget::OnCurrentScoreChanged(const uint16 NewCurrentScore) const
{
	if (IsValid(CurrentScore))
	{
		CurrentScore->SetText(FText::AsNumber(NewCurrentScore));
	}
}