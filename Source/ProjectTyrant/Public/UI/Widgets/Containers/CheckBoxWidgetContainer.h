// Vladislav Semchuk, 2025

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CheckBoxWidgetContainer.generated.h"

class UCheckBox;

/**
 * A user widget that simply contains a checkbox. It is used as a base class for sliders in this project to have shared
 * styles.
 */
UCLASS()
class PROJECTTYRANT_API UCheckboxWidgetContainer : public UUserWidget
{
	GENERATED_BODY()

public:
	UCheckBox* GetCheckBox() const { return CheckBox; }

private:
	UPROPERTY(Transient, BlueprintReadOnly, meta=(BindWidget, AllowPrivateAccess="true"))
	TObjectPtr<UCheckBox> CheckBox;
};