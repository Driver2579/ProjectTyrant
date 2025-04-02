// Vladislav Semchuk, 2025

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SliderContainerWidget.generated.h"

class USlider;

/**
 * A user widget that simply contains a slider. It is used as a base class for sliders in this project to have shared
 * styles.
 */
UCLASS()
class PROJECTTYRANT_API USliderContainerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	USlider* GetSlider() const { return Slider; }

private:
	UPROPERTY(Transient, BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess="true"))
	TObjectPtr<USlider> Slider;
};