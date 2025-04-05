// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProjectTyrant : ModuleRules
{
	public ProjectTyrant(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"Mover",
			"StateTreeModule",
			"GameplayTags"
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			
		});
	}
}
