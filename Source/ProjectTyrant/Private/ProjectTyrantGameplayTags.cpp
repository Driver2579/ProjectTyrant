// Vladislav Semchuk, 2025

#include "ProjectTyrantGameplayTags.h"

namespace ProjectTyrantGameplayTags
{
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(StateTree_Event_AI_FoundPlayer, "StateTree.Event.AI.FoundPlayer",
		"State Tree Event that is sent when AI sees the player");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(StateTree_Event_AI_LostPlayer, "StateTree.Event.AI.LostPlayer",
		"State Tree Event that is sent when AI loses the player");
}