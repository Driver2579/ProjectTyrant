// Vladislav Semchuk, 2025

#include "Actors/AddScoreTriggers/AddScoreTrigger.h"

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

	const APawn* Pawn = Cast<APawn>(OtherActor);

	if (!IsValid(Pawn) || !IsValid(Pawn->GetController<APlayerController>()))
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

void AAddScoreTrigger::OnOverlapOnce(AActor* OtherActor)
{
	BP_OnOverlapOnce(OtherActor);
}