// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CSProject : ModuleRules
{
	public CSProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule", "GameplayTasks" });
        PublicDependencyModuleNames.AddRange(new string[] {  });

        PublicIncludePaths.Add(ModuleDirectory);
    }
}
