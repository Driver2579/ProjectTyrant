// Vladislav Semchuk, 2025

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SoundSettingsMenuWidget.generated.h"

class USliderWidgetContainer;

UCLASS()
class PROJECTTYRANT_API USoundSettingsMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(Transient, meta=(BindWidget))
	TObjectPtr<USliderWidgetContainer> MasterVolumeSlider;

	UPROPERTY(Transient, meta=(BindWidget))
	TObjectPtr<USliderWidgetContainer> MusicVolumeSlider;

	UPROPERTY(Transient, meta=(BindWidget))
	TObjectPtr<USliderWidgetContainer> SFXVolumeSlider;

	void InitializeSlidersValuesFromGameUserSettings() const;

	UFUNCTION()
	void OnApplyButtonClicked() const;
};