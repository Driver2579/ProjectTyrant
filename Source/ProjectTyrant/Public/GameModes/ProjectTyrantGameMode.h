// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ProjectTyrantGameMode.generated.h"

UCLASS(MinimalAPI)
class AProjectTyrantGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AProjectTyrantGameMode();

	// Should be called when the player wins
	void Win(APlayerController* PlayerController);

	// Should be called when the player loses
	void Lose(APlayerController* PlayerController);

	// Called when the player wins or loses
	FSimpleMulticastDelegate OnGameEnded;

	FSimpleMulticastDelegate OnPlayerMadeNoise;

private:
	void EndGame(APlayerController* PlayerController);
};