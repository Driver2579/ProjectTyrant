// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameModes/ProjectTyrantGameMode.h"

#include "Characters/MoverCharacter.h"
#include "Controllers/PlayerControllers/ProjectTyrantPlayerController.h"
#include "GameStates/ScoringGameState.h"

AProjectTyrantGameMode::AProjectTyrantGameMode()
{
	GameStateClass = AScoringGameState::StaticClass();
	DefaultPawnClass = AMoverCharacter::StaticClass();
	PlayerControllerClass = AProjectTyrantPlayerController::StaticClass();
}
