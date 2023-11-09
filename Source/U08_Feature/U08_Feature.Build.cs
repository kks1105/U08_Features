// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class U08_Feature : ModuleRules
{
	public U08_Feature(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule", "ProceduralMeshComponent","Toy" });

		PublicIncludePaths.Add(ModuleDirectory);
	}

}
