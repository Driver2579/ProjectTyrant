// Vladislav Semchuk, 2025

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LoopedMusicManagerComponent.generated.h"

USTRUCT(BlueprintType)
struct FLoopedMusicPart
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> Music;

	UPROPERTY(EditAnywhere, Category="Settings", meta=(ClampMin=0))
	float CrossfadeTime = 0.25;

	// The final volume of the music part that is fading out
	UPROPERTY(EditAnywhere, Category="Settings", meta=(ClampMin=0))
	float CrossfadeVolume = 0.5;
};

USTRUCT(BlueprintType)
struct FLoopedMusic
{
	GENERATED_BODY()

	/**
	 * The start part of the music that is played once. At the end there is going to be a crossfade to the middle part
	 * of the music.
	 */
	UPROPERTY(EditAnywhere)
	FLoopedMusicPart StartPart;

	/**
	 * The middle part of the music that is played after the start part of the music is finished, and that is looped
	 * until the EndMusic or TerminateMusic function is called.
	 */
	UPROPERTY(EditAnywhere)
	FLoopedMusicPart LoopedMiddlePart;

	// The end part of the music that is played once the EndMusic function is called
	UPROPERTY(EditAnywhere)
	FLoopedMusicPart EndPart;

	UPROPERTY(EditAnywhere, Category="Settings", meta=(ClampMin=0))
	float VolumeMultiplier = 1;

	bool IsValid() const
	{
		return StartPart.Music && LoopedMiddlePart.Music && EndPart.Music;
	}
};

/**
 * This class is used to play the music split into three parts: start, middle, and end. The middle part is looped until
 * the EndMusic function is called, which plays the end part of the music. Different parts of the music can be
 * crossfaded (the first part is going to be faded out and the next part is going to be faded in).
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTTYRANT_API ULoopedMusicManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	ULoopedMusicManagerComponent();

	virtual void BeginPlay() override;

	/**
	 * Randomly selects the music from the MusicList array and plays it with the next algorithm:
	 *
	 * 1. Plays the start part of the music.
	 * 2. Once the start is finished, it plays the middle part of the music.
	 * 3. Once the middle part is finished, it plays it from the start via the crossfade effect.
	 *
	 * @remark If there is already a music playing, nothing will happen.
	 */
	void PlayMusic();
	/**
	 * Ends the currently playing music by crossfading any currently playing part of the music to the end part that is
	 * going to be played just once.
	 */
	void EndMusic();

	/**
	 * Simply stops the currently playing music without any crossfade effects and without playing the end part of the
	 * music.
	 */
	void TerminateMusic();

private:
	// Music in this array will be selected at random when PlayMusic is called
	UPROPERTY(EditAnywhere)
	TArray<FLoopedMusic> MusicList;

	int32 CurrentMusicIndex = INDEX_NONE;

	UAudioComponent* CreateAudioComponentForMusicPart(const FLoopedMusicPart& MusicPart,
		const float VolumeMultiplier) const;

	TWeakObjectPtr<UAudioComponent> CurrentMusicPartComponent;

	// Fades out the FadeOutAudioComponent and fades in the FadeInAudioComponent at the same time
	static void CrossfadeMusicParts(UAudioComponent* FadeOutAudioComponent, UAudioComponent* FadeInAudioComponent,
		const float CrossfadeTime, const float CrossfadeVolume);

	void OnStartPartPlaybackPercent(const UAudioComponent* AudioComponent, const USoundWave* PlayingSoundWave,
		const float PlaybackPercent);

	void OnMiddlePartPlaybackPercent(const UAudioComponent* AudioComponent, const USoundWave* PlayingSoundWave,
		const float PlaybackPercent);
};