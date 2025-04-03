// Vladislav Semchuk, 2025

#include "UI/Widgets/Menus/SettingsMenus/GraphicsSettingsMenuWidget.h"

#include "Common/Enums/GraphicsQualityLevel.h"
#include "Components/CheckBox.h"
#include "Components/ComboBoxString.h"
#include "GameUserSettings/ProjectTyrantGameUserSettings.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UI/Widgets/Containers/CheckBoxWidgetContainer.h"
#include "UI/Widgets/Containers/ComboBoxStringWidgetContainer.h"
#include "UI/Widgets/Menus/SettingsMenus/SettingsMenuWidget.h"

void UGraphicsSettingsMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	InitializeWindowModeComboBox();
	InitializeResolutionComboBox();
	InitializeVSyncCheckBox();
	InitializeQualityComboBoxes();

	USettingsMenuWidget* SettingsMenuWidget = GetTypedOuter<USettingsMenuWidget>();

	if (IsValid(SettingsMenuWidget))
	{
		SettingsMenuWidget->OnApply.AddUObject(this, &ThisClass::OnApplyButtonClicked);
	}
}

UProjectTyrantGameUserSettings* UGraphicsSettingsMenuWidget::GetGameUserSettings() const
{
	if (!CachedGameUserSettings.IsValid())
	{
		CachedGameUserSettings = UProjectTyrantGameUserSettings::GetProjectTyrantGameUserSettings();
	}

	return CachedGameUserSettings.Get();
}

void UGraphicsSettingsMenuWidget::InitializeWindowModeComboBox() const
{
	const UProjectTyrantGameUserSettings* GameUserSettings = GetGameUserSettings();

#if DO_CHECK
	check(IsValid(GameUserSettings));
#endif

	// Clear the existing options if any
	WindowModeComboBox->GetComboBox()->ClearOptions();

	// Add all window modes to the combo box
	for (const TTuple<TEnumAsByte<EWindowMode::Type>, FText>& WindowModeOption : WindowModeOptions)
	{
		WindowModeComboBox->GetComboBox()->AddOption(WindowModeOption.Value.ToString());
	}

	// Find the current window mode option
	const FText* CurrentWindowModeOption = WindowModeOptions.Find(GameUserSettings->GetFullscreenMode());

	// Set the current window mode as combo box's default value
	if (ensureAlways(CurrentWindowModeOption))
	{
		WindowModeComboBox->GetComboBox()->SetSelectedOption(CurrentWindowModeOption->ToString());
	}
}

void UGraphicsSettingsMenuWidget::InitializeResolutionComboBox()
{
	// Get all supported resolutions
	Resolutions.Empty();
	UKismetSystemLibrary::GetSupportedFullscreenResolutions(Resolutions);

	// Clear the existing options if any
	ResolutionComboBox->GetComboBox()->ClearOptions();

	// Add all resolutions to the combo box
	for (const FIntPoint& Resolution : Resolutions)
	{
		FString ResolutionOption = FString::Printf(TEXT("%dx%d"), Resolution.X, Resolution.Y);
		ResolutionComboBox->GetComboBox()->AddOption(ResolutionOption);
	}

	const UProjectTyrantGameUserSettings* GameUserSettings = GetGameUserSettings();

#if DO_CHECK
	check(IsValid(GameUserSettings));
#endif

	// Find the current resolution index
	const FIntPoint CurrentResolution = GameUserSettings->GetScreenResolution();
	const int32 CurrentResolutionIndex = Resolutions.IndexOfByKey(CurrentResolution);

	// Set the current resolution as combo box's default value
	if (ensureAlways(Resolutions.IsValidIndex(CurrentResolutionIndex)))
	{
		ResolutionComboBox->GetComboBox()->SetSelectedIndex(CurrentResolutionIndex);
	}
}

void UGraphicsSettingsMenuWidget::InitializeVSyncCheckBox() const
{
	const UProjectTyrantGameUserSettings* GameUserSettings = GetGameUserSettings();

#if DO_CHECK
	check(IsValid(GameUserSettings));
#endif

	VSyncCheckBox->GetCheckBox()->SetIsChecked(GameUserSettings->IsVSyncEnabled());
}

void UGraphicsSettingsMenuWidget::InitializeQualityComboBoxes() const
{
	const UProjectTyrantGameUserSettings* GameUserSettings = GetGameUserSettings();

#if DO_CHECK
	check(IsValid(GameUserSettings));
#endif

	// Clear the existing options if any
	ViewDistanceQualityComboBox->GetComboBox()->ClearOptions();
	ShadowQualityComboBox->GetComboBox()->ClearOptions();
	GlobalIlluminationQualityComboBox->GetComboBox()->ClearOptions();
	ReflectionQualityComboBox->GetComboBox()->ClearOptions();
	AntiAliasingQualityComboBox->GetComboBox()->ClearOptions();
	TextureQualityComboBox->GetComboBox()->ClearOptions();
	VisualEffectQualityComboBox->GetComboBox()->ClearOptions();
	PostProcessingQualityComboBox->GetComboBox()->ClearOptions();
	FoliageQualityComboBox->GetComboBox()->ClearOptions();
	ShadingQualityComboBox->GetComboBox()->ClearOptions();

	// Reserve space for the cached quality options to avoid reallocations
	TArray<FString> CachedQualityOptions;
	CachedQualityOptions.Reserve(static_cast<int32>(EGraphicsQuality::NumQualityLevels));

	// Cache all quality options to a string array to avoid calling FText::ToString() every time we need any
	for (const TTuple<EGraphicsQuality, FText>& QualityOption : SharedGraphicsQualityOptions)
	{
		// Insert the quality option into the index that matches the enum value
		CachedQualityOptions.Insert(QualityOption.Value.ToString(), static_cast<int32>(QualityOption.Key));
	}

	// Add all quality options to the combo boxes
	for (int32 i = 0; i < CachedQualityOptions.Num(); ++i)
	{
		ViewDistanceQualityComboBox->GetComboBox()->AddOption(CachedQualityOptions[i]);
		ShadowQualityComboBox->GetComboBox()->AddOption(CachedQualityOptions[i]);
		GlobalIlluminationQualityComboBox->GetComboBox()->AddOption(CachedQualityOptions[i]);
		ReflectionQualityComboBox->GetComboBox()->AddOption(CachedQualityOptions[i]);
		AntiAliasingQualityComboBox->GetComboBox()->AddOption(CachedQualityOptions[i]);
		TextureQualityComboBox->GetComboBox()->AddOption(CachedQualityOptions[i]);
		VisualEffectQualityComboBox->GetComboBox()->AddOption(CachedQualityOptions[i]);
		PostProcessingQualityComboBox->GetComboBox()->AddOption(CachedQualityOptions[i]);
		FoliageQualityComboBox->GetComboBox()->AddOption(CachedQualityOptions[i]);
		ShadingQualityComboBox->GetComboBox()->AddOption(CachedQualityOptions[i]);
	}

	// Set all current quality levels as combo boxes' default values
	ViewDistanceQualityComboBox->GetComboBox()->SetSelectedIndex(GameUserSettings->GetViewDistanceQuality());
	ShadowQualityComboBox->GetComboBox()->SetSelectedIndex(GameUserSettings->GetShadowQuality());
	GlobalIlluminationQualityComboBox->GetComboBox()->SetSelectedIndex(GameUserSettings->GetGlobalIlluminationQuality());
	ReflectionQualityComboBox->GetComboBox()->SetSelectedIndex(GameUserSettings->GetReflectionQuality());
	AntiAliasingQualityComboBox->GetComboBox()->SetSelectedIndex(GameUserSettings->GetAntiAliasingQuality());
	TextureQualityComboBox->GetComboBox()->SetSelectedIndex(GameUserSettings->GetTextureQuality());
	VisualEffectQualityComboBox->GetComboBox()->SetSelectedIndex(GameUserSettings->GetVisualEffectQuality());
	PostProcessingQualityComboBox->GetComboBox()->SetSelectedIndex(GameUserSettings->GetPostProcessingQuality());
	FoliageQualityComboBox->GetComboBox()->SetSelectedIndex(GameUserSettings->GetFoliageQuality());
	ShadingQualityComboBox->GetComboBox()->SetSelectedIndex(GameUserSettings->GetShadingQuality());
}

void UGraphicsSettingsMenuWidget::OnApplyButtonClicked() const
{
	UProjectTyrantGameUserSettings* GameUserSettings = GetGameUserSettings();

#if DO_CHECK
	check(IsValid(GameUserSettings));
#endif

	const FString SelectedWindowModeOption = WindowModeComboBox->GetComboBox()->GetSelectedOption();

	// Find the EWindowMode::Type value that matches the selected window mode option and set it as a window mode
	for (const TTuple<TEnumAsByte<EWindowMode::Type>, FText>& WindowModeOption : WindowModeOptions)
	{
		if (SelectedWindowModeOption.Equals(WindowModeOption.Value.ToString()))
		{
			GameUserSettings->SetFullscreenMode(WindowModeOption.Key);

			break;
		}
	}

	GameUserSettings->SetScreenResolution(Resolutions[ResolutionComboBox->GetComboBox()->GetSelectedIndex()]);
	GameUserSettings->SetVSyncEnabled(VSyncCheckBox->GetCheckBox()->IsChecked());

	GameUserSettings->SetViewDistanceQuality(
		GetGraphicsQualityIntValueFromComboBoxOption(ViewDistanceQualityComboBox->GetComboBox()->GetSelectedOption()));

	GameUserSettings->SetShadowQuality(
		GetGraphicsQualityIntValueFromComboBoxOption(ShadowQualityComboBox->GetComboBox()->GetSelectedOption()));

	GameUserSettings->SetGlobalIlluminationQuality(
		GetGraphicsQualityIntValueFromComboBoxOption(
			GlobalIlluminationQualityComboBox->GetComboBox()->GetSelectedOption()));

	GameUserSettings->SetReflectionQuality(
		GetGraphicsQualityIntValueFromComboBoxOption(ReflectionQualityComboBox->GetComboBox()->GetSelectedOption()));

	GameUserSettings->SetAntiAliasingQuality(
		GetGraphicsQualityIntValueFromComboBoxOption(AntiAliasingQualityComboBox->GetComboBox()->GetSelectedOption()));

	GameUserSettings->SetTextureQuality(
		GetGraphicsQualityIntValueFromComboBoxOption(TextureQualityComboBox->GetComboBox()->GetSelectedOption()));

	GameUserSettings->SetVisualEffectQuality(
		GetGraphicsQualityIntValueFromComboBoxOption(VisualEffectQualityComboBox->GetComboBox()->GetSelectedOption()));

	GameUserSettings->SetPostProcessingQuality(
		GetGraphicsQualityIntValueFromComboBoxOption(
			PostProcessingQualityComboBox->GetComboBox()->GetSelectedOption()));

	GameUserSettings->SetFoliageQuality(
		GetGraphicsQualityIntValueFromComboBoxOption(FoliageQualityComboBox->GetComboBox()->GetSelectedOption()));

	GameUserSettings->SetShadingQuality(
		GetGraphicsQualityIntValueFromComboBoxOption(ShadingQualityComboBox->GetComboBox()->GetSelectedOption()));

	GameUserSettings->ApplySettings(true);
}

EGraphicsQuality UGraphicsSettingsMenuWidget::GetGraphicsQualityValueFromComboBoxOption(
	const FString& ComboBoxOption) const
{
	for (const TTuple<EGraphicsQuality, FText>& QualityOption : SharedGraphicsQualityOptions)
	{
		if (ComboBoxOption.Equals(QualityOption.Value.ToString()))
		{
			return QualityOption.Key;
		}
	}

	return EGraphicsQuality::None;
}