// Vladislav Semchuk, 2025

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ProjectTyrantGameInstance.generated.h"

enum class EDifficulty : uint8;

UCLASS()
class PROJECTTYRANT_API UProjectTyrantGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

	virtual void OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld) override;
	virtual void OnWorldPreBeginPlay();

	EDifficulty GetDifficulty() const { return Difficulty; }
	void SetDifficulty(const EDifficulty NewDifficulty) { Difficulty = NewDifficulty; }

protected:
	virtual void OnApplySoundSettings();

private:
	EDifficulty Difficulty;

	// A sound mix to use and to apply the settings to
	UPROPERTY(EditDefaultsOnly, Category="Settings|Sounds")
	TObjectPtr<USoundMix> SoundMix;

	UPROPERTY(EditDefaultsOnly, Category="Settings|Sounds")
	TArray<TSoftObjectPtr<USoundClass>> MasterSoundClasses;

	UPROPERTY(EditDefaultsOnly, Category="Settings|Sounds")
	TArray<TSoftObjectPtr<USoundClass>> MusicSoundClasses;

	UPROPERTY(EditDefaultsOnly, Category="Settings|Sounds")
	TArray<TSoftObjectPtr<USoundClass>> SFXSoundClasses;
};