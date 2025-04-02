// Vladislav Semchuk, 2025

#include "UI/Widgets/PauseMenuWidget.h"

#include "Components/Button.h"
#include "Controllers/PlayerControllers/ProjectTyrantPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "UI/Widgets/ButtonContainerWidget.h"

void UPauseMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ResumeButton)
	{
		ResumeButton->GetButton()->OnClicked.AddUniqueDynamic(this, &ThisClass::OnResumeButtonClicked);
	}

	if (ExitButton)
	{
		ExitButton->GetButton()->OnClicked.AddUniqueDynamic(this, &ThisClass::OnExitButtonClicked);
	}
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UPauseMenuWidget::OnResumeButtonClicked()
{
	AProjectTyrantPlayerController* OwningPlayer = GetOwningPlayer<AProjectTyrantPlayerController>();

	if (ensureAlways(IsValid(OwningPlayer)))
	{
		OwningPlayer->ClosePauseMenu();
	}
}

// ReSharper disable once CppMemberFunctionMayBeConst
void UPauseMenuWidget::OnExitButtonClicked()
{
	if (ensureAlways(!MainMenuLevel.IsNull()))
	{
		UGameplayStatics::OpenLevelBySoftObjectPtr(this, MainMenuLevel);
	}
}