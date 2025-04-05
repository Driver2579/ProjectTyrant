// Vladislav Semchuk, 2025

#include "Actors/AddScoreTriggers/AddScoreTriggerWithPlayerNoise.h"

#include "GameModes/ProjectTyrantGameMode.h"

void AAddScoreTriggerWithPlayerNoise::OnOverlapOnce(AActor* OtherActor)
{
	Super::OnOverlapOnce(OtherActor);

	const AProjectTyrantGameMode* GameMode = GetWorld()->GetAuthGameMode<AProjectTyrantGameMode>();

	if (ensureAlways(IsValid(GameMode)))
	{
		GameMode->OnPlayerMadeNoise.Broadcast();
	}
}
