// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TimeWarp : ModuleRules
{
	public TimeWarp(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	
		DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");
	}
}
