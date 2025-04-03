// Vladislav Semchuk, 2025

#include "GameUserSettings/ProjectTyrantGameUserSettings.h"

void UProjectTyrantGameUserSettings::ApplyNonResolutionSettings()
{
	Super::ApplyNonResolutionSettings();

	ApplySoundSettings();
}

void UProjectTyrantGameUserSettings::ApplySoundSettings()
{
	OnApplySoundSettings.Broadcast();
}

void UProjectTyrantGameUserSettings::SetToDefaults()
{
	Super::SetToDefaults();

	MasterVolume = 1;
	MusicVolume = 1;
	SFXVolume = 1;
}