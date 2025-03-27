// Vladislav Semchuk, 2025

#include "UI/HUDs/ProjectTyrantHUD.h"

#include "Blueprint/UserWidget.h"

void AProjectTyrantHUD::BeginPlay()
{
	Super::BeginPlay();

	for (const TSubclassOf WidgetClass : WidgetsToCreate)
	{
		UUserWidget* CreatedWidget = CreateWidget(GetOwningPlayerController(), WidgetClass);

		if (ensureAlways(IsValid(CreatedWidget)))
		{
			CreatedWidget->AddToViewport();
		}
	}
}