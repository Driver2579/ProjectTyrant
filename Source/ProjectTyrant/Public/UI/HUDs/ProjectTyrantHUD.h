// Vladislav Semchuk, 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ProjectTyrantHUD.generated.h"

UCLASS()
class PROJECTTYRANT_API AProjectTyrantHUD : public AHUD
{
	GENERATED_BODY()

public:
	void ShowPauseMenu();
	void HidePauseMenu();

	void ShowWinWidget();
	void ShowLoseWidget();

protected:
	virtual void BeginPlay() override;

private:
	// The widgets to create at the start of the game
	UPROPERTY(EditDefaultsOnly, Category="Widgets")
	TArray<TSubclassOf<UUserWidget>> WidgetsToCreate;

	UPROPERTY(EditDefaultsOnly, Category="Cursor")
	bool bShowCursorFromStart = false;

	UPROPERTY(EditDefaultsOnly, Category="Widgets")
	TSoftClassPtr<UUserWidget> PauseMenuWidgetClass;

	TSharedPtr<struct FStreamableHandle> LoadPauseMenuWidgetClassHandle;

	void OnPauseMenuWidgetClassLoaded();

	UPROPERTY(Transient)
	TObjectPtr<UUserWidget> PauseMenuWidget;

	UPROPERTY(EditDefaultsOnly, Category="Widgets")
	TSoftClassPtr<UUserWidget> WinWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category="Widgets")
	TSoftClassPtr<UUserWidget> LoseWidgetClass;

	void OnWinWidgetLoaded() const;
	void OnLoseWidgetLoaded() const;
};