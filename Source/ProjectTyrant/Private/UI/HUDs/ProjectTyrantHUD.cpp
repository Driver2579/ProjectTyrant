// Vladislav Semchuk, 2025

#include "UI/HUDs/ProjectTyrantHUD.h"

#include "Blueprint/UserWidget.h"
#include "Engine/AssetManager.h"
#include "UI/Widgets/EndGameWidget.h"
#include "UI/Widgets/Menus/PauseMenuWidget.h"

void AProjectTyrantHUD::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* OwningPlayerController = GetOwningPlayerController();

	for (const TSubclassOf WidgetClass : WidgetsToCreate)
	{
		UUserWidget* CreatedWidget = CreateWidget(OwningPlayerController, WidgetClass);

		if (ensureAlways(IsValid(CreatedWidget)))
		{
			CreatedWidget->AddToViewport();
		}
	}

	OwningPlayerController->SetShowMouseCursor(bShowCursorFromStart);
}

void AProjectTyrantHUD::ShowPauseMenu()
{
	if (ensureAlways(!PauseMenuWidgetClass.IsNull()))
	{
		LoadPauseMenuWidgetClassHandle = UAssetManager::GetStreamableManager().RequestAsyncLoad(
			PauseMenuWidgetClass.ToSoftObjectPath(),
			FStreamableDelegate::CreateUObject(this, &ThisClass::OnPauseMenuWidgetClassLoaded));
	}
}

void AProjectTyrantHUD::OnPauseMenuWidgetClassLoaded()
{
	PauseMenuWidget = CreateWidget<UPauseMenuWidget>(GetOwningPlayerController(),
		PauseMenuWidgetClass.Get());

	PauseMenuWidget->AddToViewport();
}

void AProjectTyrantHUD::HidePauseMenu()
{
	if (ensureAlways(PauseMenuWidget))
	{
		PauseMenuWidget->RemoveFromParent();
		PauseMenuWidget = nullptr;
	}

	if (LoadPauseMenuWidgetClassHandle.IsValid())
	{
		LoadPauseMenuWidgetClassHandle->CancelHandle();
		LoadPauseMenuWidgetClassHandle.Reset();
	}
}

void AProjectTyrantHUD::ShowWinWidget()
{
	if (ensureAlways(!WinWidgetClass.IsNull()))
	{
		UAssetManager::GetStreamableManager().RequestAsyncLoad(WinWidgetClass.ToSoftObjectPath(),
			FStreamableDelegate::CreateUObject(this, &ThisClass::OnWinWidgetLoaded));
	}
}

void AProjectTyrantHUD::ShowLoseWidget()
{
	if (ensureAlways(!LoseWidgetClass.IsNull()))
	{
		UAssetManager::GetStreamableManager().RequestAsyncLoad(LoseWidgetClass.ToSoftObjectPath(),
			FStreamableDelegate::CreateUObject(this, &ThisClass::OnLoseWidgetLoaded));
	}
}

void AProjectTyrantHUD::OnWinWidgetLoaded() const
{
	APlayerController* OwningPlayerController = GetOwningPlayerController();

	UUserWidget* WinWidget = CreateWidget(OwningPlayerController, WinWidgetClass.Get());

	if (ensureAlways(IsValid(WinWidget)))
	{
		WinWidget->AddToViewport();
	}
}

void AProjectTyrantHUD::OnLoseWidgetLoaded() const
{
	APlayerController* OwningPlayerController = GetOwningPlayerController();

	UUserWidget* LoseWidget = CreateWidget(OwningPlayerController, LoseWidgetClass.Get());

	if (ensureAlways(IsValid(LoseWidget)))
	{
		LoseWidget->AddToViewport();
	}
}