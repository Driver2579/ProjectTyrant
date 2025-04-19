// Vladislav Semchuk, 2025

#include "Components/ActorComponents/LoopedMusicManagerComponent.h"

#include "Components/AudioComponent.h"
#include "GameModes/ProjectTyrantGameMode.h"
#include "Kismet/GameplayStatics.h"

ULoopedMusicManagerComponent::ULoopedMusicManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void ULoopedMusicManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	AProjectTyrantGameMode* GameMode = GetWorld()->GetAuthGameMode<AProjectTyrantGameMode>();

	// Always terminate the music when the game is ended
	if (IsValid(GameMode))
	{
		GameMode->OnGameEnded.AddUObject(this, &ThisClass::TerminateMusic);
	}
}

UAudioComponent* ULoopedMusicManagerComponent::CreateAudioComponentForMusicPart(const FLoopedMusicPart& MusicPart,
	const float VolumeMultiplier) const
{
	UAudioComponent* NewAudioComponent = UGameplayStatics::CreateSound2D(this, MusicPart.Music,
		VolumeMultiplier);

	if (!IsValid(NewAudioComponent))
	{
		return nullptr;
	}

	// We don't want to play this sound when paused
	NewAudioComponent->bIsUISound = false;

	// Support sound virtualization to make sure it isn't destroyed when the game is paused or the sound volume is 0
	NewAudioComponent->bIsVirtualized = true;

	return NewAudioComponent;
}

void ULoopedMusicManagerComponent::CrossfadeMusicParts(UAudioComponent* FadeOutAudioComponent,
	UAudioComponent* FadeInAudioComponent, const float CrossfadeTime, const float CrossfadeVolume)
{
#if DO_CHECK
	check(IsValid(FadeOutAudioComponent));
	check(IsValid(FadeInAudioComponent));
#endif

	FadeOutAudioComponent->FadeOut(CrossfadeTime, CrossfadeVolume);
	FadeInAudioComponent->FadeIn(CrossfadeTime);
}

void ULoopedMusicManagerComponent::PlayMusic()
{
	// Check if the music isn't already playing and if there is anything to play
	if (CurrentMusicIndex != INDEX_NONE || MusicList.IsEmpty())
	{
		return;
	}

	// Select the random music from the list
	const int32 MusicIndexToPlay = FMath::RandRange(0, MusicList.Num() - 1);

	if (!ensureAlways(MusicList[MusicIndexToPlay].IsValid()))
	{
		return;
	}

	// Create the AudioComponent for the start part of the music
	UAudioComponent* NewAudioComponent = CreateAudioComponentForMusicPart(MusicList[MusicIndexToPlay].StartPart,
		MusicList[MusicIndexToPlay].VolumeMultiplier);

	if (!ensureAlways(IsValid(NewAudioComponent)))
	{
		return;
	}

	// Remember the index of the music that is currently playing
	CurrentMusicIndex = MusicIndexToPlay;

	// Remember the AudioComponent that is currently playing
	CurrentMusicPartComponent = NewAudioComponent;

	/**
	 * Bind an event to know when the start part has reached the playback position where we're going to start fading it
	 * out from.
	 */
	CurrentMusicPartComponent->OnAudioPlaybackPercentNative.AddUObject(this, &ThisClass::OnStartPartPlaybackPercent);

	// Play the start part of the music after we bound the event to it
	CurrentMusicPartComponent->Play();
}

void ULoopedMusicManagerComponent::OnStartPartPlaybackPercent(const UAudioComponent* AudioComponent,
	const USoundWave* PlayingSoundWave, const float PlaybackPercent)
{
#if DO_CHECK
	check(IsValid(PlayingSoundWave));
	check(CurrentMusicPartComponent.IsValid());
	check(MusicList.IsValidIndex(CurrentMusicIndex));
#endif

	// Calculate the playback position of the music part
	const float PlaybackPosition = PlayingSoundWave->Duration * PlaybackPercent;

	// Check if we have reached the playback position where we need to start to fade out the part of the music from
	if (PlaybackPosition < PlayingSoundWave->Duration - MusicList[CurrentMusicIndex].StartPart.CrossfadeTime)
	{
		return;
	}

	// Unbind the event from the current music part's component
	CurrentMusicPartComponent->OnAudioPlaybackPercentNative.RemoveAll(this);

	// Create the AudioComponent for the middle part of the music
	UAudioComponent* NewAudioComponent = CreateAudioComponentForMusicPart(MusicList[CurrentMusicIndex].LoopedMiddlePart,
		MusicList[CurrentMusicIndex].VolumeMultiplier);

	if (!ensureAlways(IsValid(NewAudioComponent)))
	{
		return;
	}

	/**
	 * Bind an event to know when the middle part has reached the playback position where we're going to start fading it
	 * out from.
	 */
	NewAudioComponent->OnAudioPlaybackPercentNative.AddUObject(this, &ThisClass::OnMiddlePartPlaybackPercent);

	// Crossfade to the middle part of the music after we bound the event to it
	CrossfadeMusicParts(CurrentMusicPartComponent.Get(), NewAudioComponent,
		MusicList[CurrentMusicIndex].StartPart.CrossfadeTime, MusicList[CurrentMusicIndex].StartPart.CrossfadeVolume);

	// Remember the AudioComponent that is currently playing
	CurrentMusicPartComponent = NewAudioComponent;
}

void ULoopedMusicManagerComponent::OnMiddlePartPlaybackPercent(const UAudioComponent* AudioComponent,
	const USoundWave* PlayingSoundWave, const float PlaybackPercent)
{
#if DO_CHECK
	check(IsValid(PlayingSoundWave));
	check(CurrentMusicPartComponent.IsValid());
	check(MusicList.IsValidIndex(CurrentMusicIndex));
#endif

	// Calculate the playback position of the music part
	const float PlaybackPosition = PlayingSoundWave->Duration * PlaybackPercent;

	// Check if we have reached the playback position where we need to start to fade out the part of the music from
	if (PlaybackPosition < PlayingSoundWave->Duration - MusicList[CurrentMusicIndex].LoopedMiddlePart.CrossfadeTime)
	{
		return;
	}

	// Unbind the event from the current music part's component
	CurrentMusicPartComponent->OnAudioPlaybackPercentNative.RemoveAll(this);

	// Create the AudioComponent for the same part of the music to loop it
	UAudioComponent* NewAudioComponent = CreateAudioComponentForMusicPart(MusicList[CurrentMusicIndex].LoopedMiddlePart,
		MusicList[CurrentMusicIndex].VolumeMultiplier);

	if (!ensureAlways(IsValid(NewAudioComponent)))
	{
		return;
	}

	// Bind the event to know when we need to play the middle part from the start with the crossfade effect again
	NewAudioComponent->OnAudioPlaybackPercentNative.AddUObject(this, &ThisClass::OnMiddlePartPlaybackPercent);

	// Crossfade the current AudioComponent to the new one
	CrossfadeMusicParts(CurrentMusicPartComponent.Get(), NewAudioComponent,
		MusicList[CurrentMusicIndex].LoopedMiddlePart.CrossfadeTime,
		MusicList[CurrentMusicIndex].LoopedMiddlePart.CrossfadeVolume);

	// Remember the new AudioComponent as the current one
	CurrentMusicPartComponent = NewAudioComponent;
}

void ULoopedMusicManagerComponent::EndMusic()
{
	// Check if there is any music playing
	if (CurrentMusicIndex == INDEX_NONE)
	{
		return;
	}

#if DO_CHECK
	check(CurrentMusicPartComponent.IsValid());
#endif

	// Unbind the events from the current music part's component if any
	CurrentMusicPartComponent->OnAudioPlaybackPercentNative.RemoveAll(this);

	// Create the AudioComponent for the end part of the music
	UAudioComponent* NewAudioComponent = CreateAudioComponentForMusicPart(MusicList[CurrentMusicIndex].EndPart,
		MusicList[CurrentMusicIndex].VolumeMultiplier);

	if (!ensureAlways(IsValid(NewAudioComponent)))
	{
		return;
	}

	// Crossfade the current music part to the end part of the music
	CrossfadeMusicParts(CurrentMusicPartComponent.Get(), NewAudioComponent,
		MusicList[CurrentMusicIndex].EndPart.CrossfadeTime, MusicList[CurrentMusicIndex].EndPart.CrossfadeVolume);

	/**
	 * We can now say that the music is not playing anymore even though the end part is still playing to allow the new
	 * one to play.
	 */
	CurrentMusicIndex = INDEX_NONE;
	CurrentMusicPartComponent.Reset();
}

void ULoopedMusicManagerComponent::TerminateMusic()
{
	// Check if there is any music playing
	if (CurrentMusicIndex == INDEX_NONE)
	{
		return;
	}

#if DO_CHECK
	check(CurrentMusicPartComponent.IsValid());
#endif

	// Unbind the events from the current music part's component if any
	CurrentMusicPartComponent->OnAudioPlaybackPercentNative.RemoveAll(this);

	// Stop the current part of the music
	CurrentMusicPartComponent->Stop();

	// Forget about the current music
	CurrentMusicIndex = INDEX_NONE;
	CurrentMusicPartComponent.Reset();
}