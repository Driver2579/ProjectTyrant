// Vladislav Semchuk, 2025

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ProjectTyrantGameInstance.generated.h"

enum class EDifficulty : uint8;

UCLASS()
class PROJECTTYRANT_API UProjectTyrantGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	EDifficulty GetDifficulty();
	void SetDifficulty(const EDifficulty NewDifficulty) { Difficulty = NewDifficulty; }

private:
	EDifficulty Difficulty;
};