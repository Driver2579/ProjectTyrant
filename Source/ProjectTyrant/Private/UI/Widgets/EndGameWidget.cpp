// Vladislav Semchuk, 2025

#include "UI/Widgets/EndGameWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Widgets/ButtonContainerWidget.h"

void UEndGameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (RestartButton)
	{
		RestartButton->GetButton()->OnClicked.AddUniqueDynamic(this, &ThisClass::OnRestartButtonClicked);
	}

	if (GoToMainMenuButton)
	{
		GoToMainMenuButton->GetButton()->OnClicked.AddUniqueDynamic(this, &ThisClass::OnGoToMainMenuButtonClicked);
	}

	GetOwningPlayer()->SetShowMouseCursor(true);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UEndGameWidget::OnRestartButtonClicked()
{
	UGameplayStatics::OpenLevel(this,
		FName(UGameplayStatics::GetCurrentLevelName(this)));
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UEndGameWidget::OnGoToMainMenuButtonClicked()
{
	if (ensureAlways(!MainMenuLevel.IsNull()))
	{
		UGameplayStatics::OpenLevelBySoftObjectPtr(this, MainMenuLevel);
	}
}