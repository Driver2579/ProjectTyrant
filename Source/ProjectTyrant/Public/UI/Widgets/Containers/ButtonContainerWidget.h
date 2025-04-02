// Vladislav Semchuk, 2025

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ButtonContainerWidget.generated.h"

class UButton;

/**
 * A user widget that simply contains a button. It is used as a base class for buttons in this project to have shared
 * styles.
 */
UCLASS()
class PROJECTTYRANT_API UButtonContainerWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UButton* GetButton() const { return Button; }

private:
	UPROPERTY(Transient, meta=(BindWidget))
	TObjectPtr<UButton> Button;
};