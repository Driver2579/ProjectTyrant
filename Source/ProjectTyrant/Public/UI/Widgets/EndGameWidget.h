// Vladislav Semchuk, 2025

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndGameWidget.generated.h"

class UButtonContainerWidget;

/**
 * 
 */
UCLASS()
class PROJECTTYRANT_API UEndGameWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(Transient, meta=(BindWidget))
	TObjectPtr<UButtonContainerWidget> RestartButton;

	UFUNCTION()
	void OnRestartButtonClicked();

	UPROPERTY(Transient, meta=(BindWidget))
	TObjectPtr<UButtonContainerWidget> GoToMainMenuButton;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> MainMenuLevel;

	UFUNCTION()
	void OnGoToMainMenuButtonClicked();
};