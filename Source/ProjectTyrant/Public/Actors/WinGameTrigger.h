// Vladislav Semchuk, 2025

#pragma once

#include "CoreMinimal.h"
#include "WinGameTrigger.generated.h"

// Trigger that calls AProjectTyrantGameMode::Win when overlapped by the player
UCLASS()
class PROJECTTYRANT_API AWinGameTrigger : public AActor
{
	GENERATED_BODY()

public:
	AWinGameTrigger();

protected:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};