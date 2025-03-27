// Vladislav Semchuk, 2025

#include "UI/Widgets/MainMenuWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Widgets/ButtonContainerWidget.h"
#include "UI/Widgets/ChooseDifficultyWidget.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (PlayButton)
	{
		PlayButton->GetButton()->OnClicked.AddUniqueDynamic(this, &ThisClass::OnPlayButtonClicked);
	}

	if (ExitButton)
	{
		ExitButton->GetButton()->OnClicked.AddUniqueDynamic(this, &ThisClass::OnExitButtonClicked);
	}
}

void UMainMenuWidget::OnPlayButtonClicked()
{
	if (!ensureAlways(IsValid(ChooseDifficultyWidgetClass)))
	{
		return;
	}

	UChooseDifficultyWidget* ChooseDifficultyWidget = CreateWidget<UChooseDifficultyWidget>(this,
		ChooseDifficultyWidgetClass);

	if (!ensureAlways(IsValid(ChooseDifficultyWidget)))
	{
		return;
	}

	// Subscribe to the events
	ChooseDifficultyWidget->OnDifficultyChosen.AddUObject(this, &ThisClass::OnDifficultyChosen);
	ChooseDifficultyWidget->OnCanceled.AddUObject(this, &ThisClass::OnCanceledChoosingDifficulty);

	/**
	 * Remove this widget from the viewport and add the ChooseDifficultyWidget instead.
	 *
	 * Note: This widget won't be garbage collected because it's referenced by the ChooseDifficultyWidget as an
	 * OwningObject.
	 */
	RemoveFromParent();
	ChooseDifficultyWidget->AddToViewport();
}

void UMainMenuWidget::OnDifficultyChosen() const
{
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, PlayingLevel);
}

void UMainMenuWidget::OnCanceledChoosingDifficulty()
{
	// Add this widget back to the viewport
	AddToViewport();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UMainMenuWidget::OnExitButtonClicked()
{
	APlayerController* OwningPlayer = GetOwningPlayer();

	if (ensureAlways(IsValid(OwningPlayer)))
	{
		OwningPlayer->ConsoleCommand("quit");
	}
}