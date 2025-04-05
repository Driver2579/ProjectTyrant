// Vladislav Semchuk, 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AddScoreTrigger.generated.h"

// Trigger that adds score to the ScoringGameState when overlapped by the player, but only once
UCLASS()
class PROJECTTYRANT_API AAddScoreTrigger : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAddScoreTrigger();

protected:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	virtual void OnOverlapOnce(AActor* OtherActor);

	UFUNCTION(BlueprintImplementableEvent, DisplayName="On Overlap Once")
	void BP_OnOverlapOnce(AActor* OtherActor);

private:
	bool bHasOverlapped = false;
};