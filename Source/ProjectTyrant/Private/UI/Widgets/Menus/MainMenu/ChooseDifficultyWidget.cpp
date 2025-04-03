// Vladislav Semchuk, 2025

#include "UI/Widgets/Menus/MainMenu/ChooseDifficultyWidget.h"

#include "Common/Enums/Difficulty.h"
#include "Components/Button.h"
#include "GameInstances/ProjectTyrantGameInstance.h"
#include "UI/Widgets/Containers/ButtonWidgetContainer.h"

void UChooseDifficultyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (EasyButton)
	{
		EasyButton->GetButton()->OnClicked.AddDynamic(this, &ThisClass::OnEasyButtonClicked);
	}

	if (NormalButton)
	{
		NormalButton->GetButton()->OnClicked.AddDynamic(this, &ThisClass::OnNormalButtonClicked);
	}

	if (HardButton)
	{
		HardButton->GetButton()->OnClicked.AddDynamic(this, &ThisClass::OnHardButtonClicked);
	}

	if (CancelButton)
	{
		CancelButton->GetButton()->OnClicked.AddDynamic(this, &ThisClass::OnCancelButtonClicked);
	}
}

void UChooseDifficultyWidget::OnEasyButtonClicked()
{
	ChooseDifficulty(EDifficulty::Easy);
}

void UChooseDifficultyWidget::OnNormalButtonClicked()
{
	ChooseDifficulty(EDifficulty::Normal);
}

void UChooseDifficultyWidget::OnHardButtonClicked()
{
	ChooseDifficulty(EDifficulty::Hard);
}

void UChooseDifficultyWidget::ChooseDifficulty(const EDifficulty Difficulty)
{
	UProjectTyrantGameInstance* ProjectTyrantGameInstance = GetGameInstance<UProjectTyrantGameInstance>();

	if (ensureAlways(IsValid(ProjectTyrantGameInstance)))
	{
		ProjectTyrantGameInstance->SetDifficulty(Difficulty);
	}

	OnDifficultyChosen.Broadcast();

	RemoveFromParent();
}

void UChooseDifficultyWidget::OnCancelButtonClicked()
{
	RemoveFromParent();

	OnCanceled.Broadcast();
}