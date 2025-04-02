// Vladislav Semchuk, 2025

#include "GameUserSettings/ProjectTyrantGameUserSettings.h"

#include "AudioDevice.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundClass.h"

void UProjectTyrantGameUserSettings::LoadSettings(const bool bForceReload)
{
	Super::LoadSettings(bForceReload);

	UGameplayStatics::SetBaseSoundMix(this, SoundMix);
}

void UProjectTyrantGameUserSettings::ApplyNonResolutionSettings()
{
	Super::ApplyNonResolutionSettings();

	ApplySoundSettings();
}

void UProjectTyrantGameUserSettings::ApplySoundSettings()
{
	if (!ensureAlways(SoundMix))
	{
		return;
	}

	const UWorld* World = GEngine->GetWorld();

	// TODO: This is always null. Need to create a workaround.
	if (!IsValid(World))
	{
		return;
	}

	FAudioDeviceHandle AudioDevice = World->GetAudioDevice();

	if (!AudioDevice.IsValid())
	{
		return;
	}

	for (const TSoftObjectPtr<USoundClass>& SoundClassSoftPtr : MasterSoundClasses)
	{
		USoundClass* SoundClass = SoundClassSoftPtr.LoadSynchronous();

		AudioDevice->SetSoundMixClassOverride(SoundMix, SoundClass, MasterVolume, 1, 1,
			true);
	}

	for (const TSoftObjectPtr<USoundClass>& SoundClassSoftPtr : MusicSoundClasses)
	{
		USoundClass* SoundClass = SoundClassSoftPtr.LoadSynchronous();

		AudioDevice->SetSoundMixClassOverride(SoundMix, SoundClass, MusicVolume, 1, 1,
			true);
	}

	for (const TSoftObjectPtr<USoundClass>& SoundClassSoftPtr : SFXSoundClasses)
	{
		USoundClass* SoundClass = SoundClassSoftPtr.LoadSynchronous();

		AudioDevice->SetSoundMixClassOverride(SoundMix, SoundClass, SFXVolume, 1, 1,
			true);
	}
}

void UProjectTyrantGameUserSettings::SetToDefaults()
{
	Super::SetToDefaults();

	MasterVolume = 1;
	MusicVolume = 1;
	SFXVolume = 1;
}