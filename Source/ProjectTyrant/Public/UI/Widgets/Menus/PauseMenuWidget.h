// Vladislav Semchuk, 2025

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenuWidget.generated.h"

class USettingsMenuWidget;
class UButtonContainerWidget;

UCLASS()
class PROJECTTYRANT_API UPauseMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	UPROPERTY(Transient, meta=(BindWidget))
	TObjectPtr<UButtonContainerWidget> ResumeButton;

	UFUNCTION()
	void OnResumeButtonClicked();

	UPROPERTY(Transient, meta=(BindWidget))
	TObjectPtr<UButtonContainerWidget> SettingsButton;

	UPROPERTY(EditDefaultsOnly, Category="Settings")
	TSubclassOf<USettingsMenuWidget> SettingsMenuWidgetClass;

	UPROPERTY(Transient)
	TObjectPtr<USettingsMenuWidget> SettingsMenuWidget;

	UFUNCTION()
	void OnSettingsButtonClicked();

	void OnSettingsMenuBackButtonClicked();

	UPROPERTY(Transient, meta=(BindWidget))
	TObjectPtr<UButtonContainerWidget> ExitButton;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> MainMenuLevel;

	UFUNCTION()
	void OnExitButtonClicked();
};