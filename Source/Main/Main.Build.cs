// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Main : ModuleRules
{
	public Main(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Paper2D" });

		//PrivateDependencyModuleNames.AddRange(new string[] {  });

		PublicIncludePaths.Add(ModuleDirectory);

	}
}
