// Vladislav Semchuk, 2025

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndGameWidget.generated.h"

class UButtonWidgetContainer;

UCLASS()
class PROJECTTYRANT_API UEndGameWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(EditDefaultsOnly, Category="Sounds")
	TObjectPtr<USoundBase> SoundToPlayOnConstruct;

	UPROPERTY(Transient, meta=(BindWidget))
	TObjectPtr<UButtonWidgetContainer> RestartButton;

	UFUNCTION()
	void OnRestartButtonClicked();

	UPROPERTY(Transient, meta=(BindWidget))
	TObjectPtr<UButtonWidgetContainer> GoToMainMenuButton;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> MainMenuLevel;

	UFUNCTION()
	void OnGoToMainMenuButtonClicked();
};