// Vladislav Semchuk, 2025

#include "UI/Widgets/Menus/SettingsMenus/SettingsMenuWidget.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "UI/Widgets/Containers/ButtonContainerWidget.h"
#include "UI/Widgets/Menus/SettingsMenus/GraphicsSettingsMenuWidget.h"
#include "UI/Widgets/Menus/SettingsMenus/SoundSettingsMenuWidget.h"

void USettingsMenuWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (!SettingsWidgetsSwitcher)
	{
		return;
	}

	if (ensureAlways(IsValid(GraphicsSettingsMenuWidgetClass)))
	{
		GraphicsSettingsMenuWidget = CreateWidget<UGraphicsSettingsMenuWidget>(this,
			GraphicsSettingsMenuWidgetClass);

		SettingsWidgetsSwitcher->AddChild(GraphicsSettingsMenuWidget);
		SettingsWidgetsSwitcher->SetActiveWidget(GraphicsSettingsMenuWidget);
	}

	if (ensureAlways(IsValid(SoundSettingsMenuWidgetClass)))
	{
		SoundSettingsMenuWidget = CreateWidget<USoundSettingsMenuWidget>(this,
			SoundSettingsMenuWidgetClass);

		SettingsWidgetsSwitcher->AddChild(SoundSettingsMenuWidget);
	}
}

void USettingsMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (OpenGraphicsSettingsButton)
	{
		OpenGraphicsSettingsButton->GetButton()->OnClicked.AddUniqueDynamic(this,
			&ThisClass::OnGraphicsSettingsMenuBackButtonClicked);
	}

	if (OpenSoundSettingsButton)
	{
		OpenSoundSettingsButton->GetButton()->OnClicked.AddUniqueDynamic(this,
			&ThisClass::OnSoundSettingsMenuBackButtonClicked);
	}

	if (ApplyButton)
	{
		ApplyButton->GetButton()->OnClicked.AddUniqueDynamic(this, &ThisClass::OnApplyButtonClicked);
	}

	if (BackButton)
	{
		BackButton->GetButton()->OnClicked.AddUniqueDynamic(this, &ThisClass::OnBackButtonClicked);
	}
}

// ReSharper disable CppMemberFunctionMayBeConst
void USettingsMenuWidget::OnGraphicsSettingsMenuBackButtonClicked()
{
#if DO_CHECK
	check(SettingsWidgetsSwitcher);
#endif

	if (ensureAlways(GraphicsSettingsMenuWidget))
	{
		SettingsWidgetsSwitcher->SetActiveWidget(GraphicsSettingsMenuWidget);
	}
}

void USettingsMenuWidget::OnSoundSettingsMenuBackButtonClicked()
{
#if DO_CHECK
	check(SettingsWidgetsSwitcher);
#endif

	if (ensureAlways(SoundSettingsMenuWidget))
	{
		SettingsWidgetsSwitcher->SetActiveWidget(SoundSettingsMenuWidget);
	}
}
// ReSharper restore CppMemberFunctionMayBeConst

// ReSharper disable once CppMemberFunctionMayBeConst
void USettingsMenuWidget::OnApplyButtonClicked()
{
	OnApply.Broadcast();
}

void USettingsMenuWidget::OnBackButtonClicked()
{
	RemoveFromParent();

	OnBack.Broadcast();
}