// Vladislav Semchuk, 2025

#pragma once

UENUM(BlueprintType)
enum class EDifficulty : uint8
{
	Easy,
	Normal,
	Hard,

	None UMETA(Hidden)
};