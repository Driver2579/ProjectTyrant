// Vladislav Semchuk, 2025

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TargetScoreTriggeredActor.generated.h"

// Actor that listens to the target score being reached and calls OnTargetScoreReached when it happens
UCLASS()
class PROJECTTYRANT_API ATargetScoreTriggeredActor : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ATargetScoreTriggeredActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called when the target score is reached. Should be overridden by child classes.
	UFUNCTION(BlueprintNativeEvent)
	void OnTargetScoreReached();
};