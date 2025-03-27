// Vladislav Semchuk, 2025

#include "Actors/TargetScoreTriggeredActor.h"

#include "GameStates/ScoringGameState.h"

ATargetScoreTriggeredActor::ATargetScoreTriggeredActor()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
}

void ATargetScoreTriggeredActor::BeginPlay()
{
	Super::BeginPlay();

	AScoringGameState* ScoringGameState = GetWorld()->GetGameState<AScoringGameState>();

	if (IsValid(ScoringGameState))
	{
		ScoringGameState->CallOrRegister_OnTargetScoreReached(
			FSimpleMulticastDelegate::FDelegate::CreateUObject(this, &ThisClass::OnTargetScoreReached));
	}
}

void ATargetScoreTriggeredActor::OnTargetScoreReached_Implementation()
{
}