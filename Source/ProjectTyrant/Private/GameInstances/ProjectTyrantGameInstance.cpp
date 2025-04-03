// Vladislav Semchuk, 2025

#include "GameInstances/ProjectTyrantGameInstance.h"

#include "AudioDevice.h"
#include "GameUserSettings/ProjectTyrantGameUserSettings.h"
#include "Kismet/GameplayStatics.h"

void UProjectTyrantGameInstance::Init()
{
	Super::Init();

	UProjectTyrantGameUserSettings* GameUserSettings =
		UProjectTyrantGameUserSettings::GetProjectTyrantGameUserSettings();

	if (ensureAlways(IsValid(GameUserSettings)))
	{
		GameUserSettings->OnApplySoundSettings.AddUObject(this, &ThisClass::OnApplySoundSettings);
	}
}

void UProjectTyrantGameInstance::OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld)
{
	Super::OnWorldChanged(OldWorld, NewWorld);

	if (IsValid(NewWorld))
	{
		NewWorld->OnWorldPreBeginPlay.AddUObject(this, &ThisClass::OnWorldPreBeginPlay);
	}
}

void UProjectTyrantGameInstance::OnWorldPreBeginPlay()
{
#if DO_ENSURE
	ensureAlways(SoundMix);
#endif

	UGameplayStatics::SetBaseSoundMix(this, SoundMix);
	OnApplySoundSettings();
}

void UProjectTyrantGameInstance::OnApplySoundSettings()
{
#if DO_ENSURE
	ensureAlways(SoundMix);
#endif

	const UProjectTyrantGameUserSettings* GameUserSettings =
		UProjectTyrantGameUserSettings::GetProjectTyrantGameUserSettings();

	if (!ensureAlways(IsValid(GameUserSettings)))
	{
		return;
	}

	FAudioDeviceHandle AudioDevice = GetWorld()->GetAudioDevice();

	if (!AudioDevice.IsValid())
	{
		return;
	}

	for (const TSoftObjectPtr<USoundClass>& SoundClassSoftPtr : MasterSoundClasses)
	{
		USoundClass* SoundClass = SoundClassSoftPtr.LoadSynchronous();

		AudioDevice->SetSoundMixClassOverride(SoundMix, SoundClass, GameUserSettings->GetMasterVolume(), 1,
			1, true);
	}

	for (const TSoftObjectPtr<USoundClass>& SoundClassSoftPtr : MusicSoundClasses)
	{
		USoundClass* SoundClass = SoundClassSoftPtr.LoadSynchronous();

		AudioDevice->SetSoundMixClassOverride(SoundMix, SoundClass, GameUserSettings->GetMusicVolume(), 1,
			1, true);
	}

	for (const TSoftObjectPtr<USoundClass>& SoundClassSoftPtr : SFXSoundClasses)
	{
		USoundClass* SoundClass = SoundClassSoftPtr.LoadSynchronous();

		AudioDevice->SetSoundMixClassOverride(SoundMix, SoundClass, GameUserSettings->GetSFXVolume(), 1,
			1, true);
	}
}