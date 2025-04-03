// Vladislav Semchuk, 2025

#include "UI/Widgets/Menus/PauseMenuWidget.h"

#include "Components/Button.h"
#include "Controllers/PlayerControllers/ProjectTyrantPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Widgets/Containers/ButtonWidgetContainer.h"
#include "UI/Widgets/Menus/SettingsMenus/SettingsMenuWidget.h"

void UPauseMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ResumeButton)
	{
		ResumeButton->GetButton()->OnClicked.AddUniqueDynamic(this, &ThisClass::OnResumeButtonClicked);
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

void UPauseMenuWidget::NativeDestruct()
{
	if (SettingsMenuWidget)
	{
		SettingsMenuWidget->RemoveFromParent();
		SettingsMenuWidget = nullptr;
	}

	Super::NativeDestruct();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UPauseMenuWidget::OnResumeButtonClicked()
{
	AProjectTyrantPlayerController* OwningPlayer = GetOwningPlayer<AProjectTyrantPlayerController>();

	if (ensureAlways(IsValid(OwningPlayer)))
	{
		OwningPlayer->ClosePauseMenu();
	}
}

void UPauseMenuWidget::OnSettingsButtonClicked()
{
	if (!ensureAlways(IsValid(SettingsMenuWidgetClass)))
	{
		return;
	}

	SettingsMenuWidget = CreateWidget<USettingsMenuWidget>(this, SettingsMenuWidgetClass);

	if (!ensureAlways(IsValid(SettingsMenuWidget)))
	{
		return;
	}

	// Subscribe to the events
	SettingsMenuWidget->OnBack.AddUObject(this, &ThisClass::OnSettingsMenuBackButtonClicked);

	SetVisibility(ESlateVisibility::Hidden);
	SettingsMenuWidget->AddToViewport();
}

void UPauseMenuWidget::OnSettingsMenuBackButtonClicked()
{
	SetVisibility(ESlateVisibility::Visible);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UPauseMenuWidget::OnExitButtonClicked()
{
	if (ensureAlways(!MainMenuLevel.IsNull()))
	{
		UGameplayStatics::OpenLevelBySoftObjectPtr(this, MainMenuLevel);
	}
}