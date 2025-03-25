// Vladislav Semchuk, 2025

#include "Actors/AddScoreTrigger.h"

#include "GameStates/ScoringGameState.h"

AAddScoreTrigger::AAddScoreTrigger()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
}

void AAddScoreTrigger::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (bHasOverlapped)
	{
		return;
	}

	AScoringGameState* ScoringGameState = GetWorld()->GetGameState<AScoringGameState>();

	if (IsValid(ScoringGameState))
	{
		ScoringGameState->AddScore();
	}

	OnOverlapOnce(OtherActor);

	bHasOverlapped = true;
}

void AAddScoreTrigger::OnOverlapOnce_Implementation(AActor* OtherActor)
{
}