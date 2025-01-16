// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SpeedrunShooter : ModuleRules
{
	public SpeedrunShooter(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "NavigationSystem","Core", "CoreUObject","UMG", "Engine", "InputCore", "EnhancedInput", "AIModule", "Niagara" });
	}
}
