// Vladislav Semchuk, 2025

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChooseDifficultyWidget.generated.h"

class UButtonContainerWidget;

enum class EDifficulty : uint8;

/**
 * The widget that allows the player to choose the difficulty of the game. Once selected, it writes the choice to the
 * game instance, broadcasts the OnDifficultyChosen delegate and closes itself.
 */
UCLASS()
class PROJECTTYRANT_API UChooseDifficultyWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	// Called when the player chooses the difficulty
	FSimpleMulticastDelegate OnDifficultyChosen;

	// Called when the player cancels the difficulty selection
	FSimpleMulticastDelegate OnCanceled;

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(Transient, meta=(BindWidget))
	TObjectPtr<UButtonContainerWidget> EasyButton;

	UPROPERTY(Transient, meta=(BindWidget))
	TObjectPtr<UButtonContainerWidget> NormalButton;

	UPROPERTY(Transient, meta=(BindWidget))
	TObjectPtr<UButtonContainerWidget> HardButton;

	UFUNCTION()
	void OnEasyButtonClicked();

	UFUNCTION()
	void OnNormalButtonClicked();

	UFUNCTION()
	void OnHardButtonClicked();

	void ChooseDifficulty(const EDifficulty NewDifficulty);

	// When clicked, simply closes the widget without choosing the difficulty
	UPROPERTY(Transient, meta=(BindWidget))
	TObjectPtr<UButtonContainerWidget> CancelButton;

	UFUNCTION()
	void OnCancelButtonClicked();
};