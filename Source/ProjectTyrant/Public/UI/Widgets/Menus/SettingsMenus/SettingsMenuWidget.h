﻿// Vladislav Semchuk, 2025

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SettingsMenuWidget.generated.h"

class UButtonWidgetContainer;
class USoundSettingsMenuWidget;
class UGraphicsSettingsMenuWidget;

UCLASS()
class PROJECTTYRANT_API USettingsMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FSimpleMulticastDelegate OnApply;
	FSimpleMulticastDelegate OnBack;

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

private:
	UPROPERTY(Transient, meta=(BindWidget))
	TObjectPtr<UButtonWidgetContainer> OpenGraphicsSettingsButton;

	UPROPERTY(Transient, meta=(BindWidget))
	TObjectPtr<UButtonWidgetContainer> OpenSoundSettingsButton;

	UFUNCTION()
	void OnGraphicsSettingsMenuBackButtonClicked();

	UFUNCTION()
	void OnSoundSettingsMenuBackButtonClicked();

	UPROPERTY(Transient, meta=(BindWidget))
	TObjectPtr<class UWidgetSwitcher> SettingsWidgetsSwitcher;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGraphicsSettingsMenuWidget> GraphicsSettingsMenuWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USoundSettingsMenuWidget> SoundSettingsMenuWidgetClass;

	UPROPERTY(Transient)
	TObjectPtr<UGraphicsSettingsMenuWidget> GraphicsSettingsMenuWidget;

	UPROPERTY(Transient)
	TObjectPtr<USoundSettingsMenuWidget> SoundSettingsMenuWidget;

	UPROPERTY(Transient, meta=(BindWidget))
	TObjectPtr<UButtonWidgetContainer> ApplyButton;

	UPROPERTY(Transient, meta=(BindWidget))
	TObjectPtr<UButtonWidgetContainer> BackButton;

	UFUNCTION()
	void OnApplyButtonClicked();

	UFUNCTION()
	void OnBackButtonClicked();
};