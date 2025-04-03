// Vladislav Semchuk, 2025

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class UButtonWidgetContainer;

// The widget that contains all elements of the main menu
UCLASS()
class PROJECTTYRANT_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

private:
	// Opens the ChooseDifficultyWidget and starts the game once the difficulty is chosen
	UPROPERTY(Transient, meta=(BindWidget))
	TObjectPtr<UButtonWidgetContainer> PlayButton;

	// The widget that shows up when the player presses the Play button. Once the difficulty is chosen, the game starts.
	UPROPERTY(EditDefaultsOnly, Category="Play")
	TSubclassOf<class UChooseDifficultyWidget> ChooseDifficultyWidgetClass;

	UFUNCTION()
	void OnPlayButtonClicked();

	void OnDifficultyChosen() const;
	void OnCanceledChoosingDifficulty();

	// The level to load when the player presses the Play button
	UPROPERTY(EditDefaultsOnly, Category="Play")
	TSoftObjectPtr<UWorld> PlayingLevel;

	UPROPERTY(Transient, meta=(BindWidget))
	TObjectPtr<UButtonWidgetContainer> SettingsButton;

	UPROPERTY(EditDefaultsOnly, Category="Settings")
	TSubclassOf<class USettingsMenuWidget> SettingsMenuWidgetClass;

	UFUNCTION()
	void OnSettingsButtonClicked();

	void OnSettingsMenuBackButtonClicked();

	// Closes the game
	UPROPERTY(Transient, meta=(BindWidget))
	TObjectPtr<UButtonWidgetContainer> ExitButton;

	UFUNCTION()
	void OnExitButtonClicked();
};