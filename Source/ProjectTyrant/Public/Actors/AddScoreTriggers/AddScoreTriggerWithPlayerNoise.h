// Vladislav Semchuk, 2025

#pragma once

#include "CoreMinimal.h"
#include "AddScoreTrigger.h"
#include "AddScoreTriggerWithPlayerNoise.generated.h"

// Calls AProjectTyrantGameMode::OnPlayerMadeNoise when overlapped once
UCLASS()
class PROJECTTYRANT_API AAddScoreTriggerWithPlayerNoise : public AAddScoreTrigger
{
	GENERATED_BODY()

protected:
	virtual void OnOverlapOnce(AActor* OtherActor) override;
};