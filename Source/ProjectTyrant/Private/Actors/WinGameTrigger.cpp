// Vladislav Semchuk, 2025

#include "Actors/WinGameTrigger.h"

#include "GameModes/ProjectTyrantGameMode.h"

AWinGameTrigger::AWinGameTrigger()
{
	PrimaryActorTick.bCanEverTick = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
}

void AWinGameTrigger::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	const APawn* Pawn = Cast<APawn>(OtherActor);

	if (!IsValid(Pawn))
	{
		return;
	}

	APlayerController* PlayerController = Pawn->GetController<APlayerController>();

	if (!IsValid(PlayerController))
	{
		return;
	}

	AProjectTyrantGameMode* GameMode = GetWorld()->GetAuthGameMode<AProjectTyrantGameMode>();

	if (IsValid(GameMode))
	{
		GameMode->Win(PlayerController);
	}
}