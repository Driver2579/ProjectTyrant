// Vladislav Semchuk, 2025

#include "UI/HUDs/ProjectTyrantHUD.h"

#include "Blueprint/UserWidget.h"

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