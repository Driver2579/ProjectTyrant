// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameModes/ProjectTyrantGameMode.h"

#include "Characters/MoverCharacter.h"
#include "Controllers/PlayerControllers/ProjectTyrantPlayerController.h"

AProjectTyrantGameMode::AProjectTyrantGameMode()
{
	DefaultPawnClass = AMoverCharacter::StaticClass();
	PlayerControllerClass = AProjectTyrantPlayerController::StaticClass();
}