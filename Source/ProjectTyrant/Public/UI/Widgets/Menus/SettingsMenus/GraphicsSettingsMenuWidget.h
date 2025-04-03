// Vladislav Semchuk, 2025

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GraphicsSettingsMenuWidget.generated.h"

class UCheckboxWidgetContainer;
class UProjectTyrantGameUserSettings;
class UComboBoxStringWidgetContainer;

enum class EGraphicsQuality : uint8;

UCLASS()
class PROJECTTYRANT_API UGraphicsSettingsMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UProjectTyrantGameUserSettings* GetGameUserSettings() const;

private:
	mutable TWeakObjectPtr<UProjectTyrantGameUserSettings> CachedGameUserSettings;

	UPROPERTY(Transient, meta=(BindWidget))
	TObjectPtr<UComboBoxStringWidgetContainer> WindowModeComboBox;

	UPROPERTY(EditDefaultsOnly, Category="Settings")
	TMap<TEnumAsByte<EWindowMode::Type>, FText> WindowModeOptions;

	void InitializeWindowModeComboBox() const;

	UPROPERTY(Transient, meta=(BindWidget))
	TObjectPtr<UComboBoxStringWidgetContainer> ResolutionComboBox;

	void InitializeResolutionComboBox();

	TArray<FIntPoint> Resolutions;

	UPROPERTY(Transient, meta=(BindWidget))
	TObjectPtr<UCheckboxWidgetContainer> VSyncCheckBox;

	void InitializeVSyncCheckBox() const;

	// Options from this map are going to be used for all graphics quality levels that support this format
	UPROPERTY(EditDefaultsOnly, Category="Settings")
	TMap<EGraphicsQuality, FText> SharedGraphicsQualityOptions;

	UPROPERTY(Transient, meta=(BindWidget))
	TObjectPtr<UComboBoxStringWidgetContainer> ViewDistanceQualityComboBox;

	UPROPERTY(Transient, meta=(BindWidget))
	TObjectPtr<UComboBoxStringWidgetContainer> ShadowQualityComboBox;

	UPROPERTY(Transient, meta=(BindWidget))
	TObjectPtr<UComboBoxStringWidgetContainer> GlobalIlluminationQualityComboBox;

	UPROPERTY(Transient, meta=(BindWidget))
	TObjectPtr<UComboBoxStringWidgetContainer> ReflectionQualityComboBox;

	UPROPERTY(Transient, meta=(BindWidget))
	TObjectPtr<UComboBoxStringWidgetContainer> AntiAliasingQualityComboBox;

	UPROPERTY(Transient, meta=(BindWidget))
	TObjectPtr<UComboBoxStringWidgetContainer> TextureQualityComboBox;

	UPROPERTY(Transient, meta=(BindWidget))
	TObjectPtr<UComboBoxStringWidgetContainer> VisualEffectQualityComboBox;

	UPROPERTY(Transient, meta=(BindWidget))
	TObjectPtr<UComboBoxStringWidgetContainer> PostProcessingQualityComboBox;

	UPROPERTY(Transient, meta=(BindWidget))
	TObjectPtr<UComboBoxStringWidgetContainer> FoliageQualityComboBox;

	UPROPERTY(Transient, meta=(BindWidget))
	TObjectPtr<UComboBoxStringWidgetContainer> ShadingQualityComboBox;

	void InitializeQualityComboBoxes() const;

	UFUNCTION()
	void OnApplyButtonClicked() const;

	// Finds the EGraphicsQuality value that matches the selected graphics quality option and returns it
	EGraphicsQuality GetGraphicsQualityValueFromComboBoxOption(const FString& ComboBoxOption) const;

	int32 GetGraphicsQualityIntValueFromComboBoxOption(const FString& ComboBoxOption) const
	{
		return static_cast<int32>(GetGraphicsQualityValueFromComboBoxOption(ComboBoxOption));
	}
};