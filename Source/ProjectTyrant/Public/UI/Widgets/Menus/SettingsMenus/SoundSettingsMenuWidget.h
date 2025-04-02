// Vladislav Semchuk, 2025

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SoundSettingsMenuWidget.generated.h"

class USliderContainerWidget;

UCLASS()
class PROJECTTYRANT_API USoundSettingsMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(Transient, meta=(BindWidget))
	TObjectPtr<USliderContainerWidget> MasterVolumeSlider;

	UPROPERTY(Transient, meta=(BindWidget))
	TObjectPtr<USliderContainerWidget> MusicVolumeSlider;

	UPROPERTY(Transient, meta=(BindWidget))
	TObjectPtr<USliderContainerWidget> SFXVolumeSlider;

	void InitializeSlidersValuesFromGameUserSettings() const;

	UFUNCTION()
	void OnApplyButtonClicked() const;
};