// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameModes/ProjectTyrantGameMode.h"

#include "Characters/MoverCharacter.h"
#include "Controllers/PlayerControllers/ProjectTyrantPlayerController.h"
#include "GameStates/ScoringGameState.h"
#include "UI/HUDs/ProjectTyrantHUD.h"

AProjectTyrantGameMode::AProjectTyrantGameMode()
{
	GameStateClass = AScoringGameState::StaticClass();
	DefaultPawnClass = AMoverCharacter::StaticClass();
	PlayerControllerClass = AProjectTyrantPlayerController::StaticClass();
	HUDClass = AProjectTyrantHUD::StaticClass();
}

void AProjectTyrantGameMode::Win(APlayerController* PlayerController)
{
#if DO_CHECK
	check(IsValid(PlayerController));
#endif

	AProjectTyrantHUD* HUD = PlayerController->GetHUD<AProjectTyrantHUD>();

	if (ensureAlways(IsValid(HUD)))
	{
		HUD->ShowWinWidget();
	}

	EndGame(PlayerController);
}

void AProjectTyrantGameMode::Lose(APlayerController* PlayerController)
{
#if DO_CHECK
	check(IsValid(PlayerController));
#endif

	AProjectTyrantHUD* HUD = PlayerController->GetHUD<AProjectTyrantHUD>();

	if (ensureAlways(IsValid(HUD)))
	{
		HUD->ShowLoseWidget();
	}

	EndGame(PlayerController);
}

void AProjectTyrantGameMode::EndGame(APlayerController* PlayerController)
{
#if DO_CHECK
	check(IsValid(PlayerController));
#endif

	PlayerController->DisableInput(PlayerController);
	SetPause(PlayerController);
}