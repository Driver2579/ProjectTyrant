// Vladislav Semchuk, 2025

#include "UI/Widgets/Menus/SettingsMenus/SoundSettingsMenuWidget.h"

#include "Components/Slider.h"
#include "GameUserSettings/ProjectTyrantGameUserSettings.h"
#include "UI/Widgets/Containers/ButtonWidgetContainer.h"
#include "UI/Widgets/Containers/SliderWidgetContainer.h"
#include "UI/Widgets/Menus/SettingsMenus/SettingsMenuWidget.h"

void USoundSettingsMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeSlidersValuesFromGameUserSettings();

	USettingsMenuWidget* SettingsMenuWidget = GetTypedOuter<USettingsMenuWidget>();

	if (IsValid(SettingsMenuWidget))
	{
		SettingsMenuWidget->OnApply.AddUObject(this, &ThisClass::OnApplyButtonClicked);
	}
}

void USoundSettingsMenuWidget::InitializeSlidersValuesFromGameUserSettings() const
{
	const UProjectTyrantGameUserSettings* GameUserSettings =
		UProjectTyrantGameUserSettings::GetProjectTyrantGameUserSettings();

	if (MasterVolumeSlider)
	{
		MasterVolumeSlider->GetSlider()->SetValue(GameUserSettings->GetMasterVolume());
	}

	if (MusicVolumeSlider)
	{
		MusicVolumeSlider->GetSlider()->SetValue(GameUserSettings->GetMusicVolume());
	}

	if (SFXVolumeSlider)
	{
		SFXVolumeSlider->GetSlider()->SetValue(GameUserSettings->GetSFXVolume());
	}
}

void USoundSettingsMenuWidget::OnApplyButtonClicked() const
{
	UProjectTyrantGameUserSettings* GameUserSettings =
		UProjectTyrantGameUserSettings::GetProjectTyrantGameUserSettings();

	GameUserSettings->SetMasterVolume(MasterVolumeSlider->GetSlider()->GetValue());
	GameUserSettings->SetMusicVolume(MusicVolumeSlider->GetSlider()->GetValue());
	GameUserSettings->SetSFXVolume(SFXVolumeSlider->GetSlider()->GetValue());

	GameUserSettings->ApplySoundSettings();
	GameUserSettings->SaveSettings();
}