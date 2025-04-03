// Vladislav Semchuk, 2025

#include "UI/Widgets/Menus/MainMenu/MainMenuWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Widgets/Containers/ButtonWidgetContainer.h"
#include "UI/Widgets/Menus/MainMenu/ChooseDifficultyWidget.h"
#include "UI/Widgets/Menus/SettingsMenus/SettingsMenuWidget.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (PlayButton)
	{
		PlayButton->GetButton()->OnClicked.AddUniqueDynamic(this, &ThisClass::OnPlayButtonClicked);
	}

	if (SettingsButton)
	{
		SettingsButton->GetButton()->OnClicked.AddUniqueDynamic(this, &ThisClass::OnSettingsButtonClicked);
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

	SetVisibility(ESlateVisibility::Hidden);
	ChooseDifficultyWidget->AddToViewport();
}

void UMainMenuWidget::OnDifficultyChosen() const
{
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, PlayingLevel);
}

void UMainMenuWidget::OnCanceledChoosingDifficulty()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UMainMenuWidget::OnSettingsButtonClicked()
{
	if (!ensureAlways(IsValid(SettingsMenuWidgetClass)))
	{
		return;
	}

	USettingsMenuWidget* SettingsMenuWidget = CreateWidget<USettingsMenuWidget>(this,
		SettingsMenuWidgetClass);

	if (!ensureAlways(IsValid(SettingsMenuWidget)))
	{
		return;
	}

	// Subscribe to the events
	SettingsMenuWidget->OnBack.AddUObject(this, &ThisClass::OnSettingsMenuBackButtonClicked);

	SetVisibility(ESlateVisibility::Hidden);
	SettingsMenuWidget->AddToViewport();
}

void UMainMenuWidget::OnSettingsMenuBackButtonClicked()
{
	SetVisibility(ESlateVisibility::Visible);
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