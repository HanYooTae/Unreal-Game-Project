// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Main : ModuleRules
{
	public Main(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicIncludePaths.Add(ModuleDirectory);

		PublicDependencyModuleNames.Add("Core");
		PublicDependencyModuleNames.Add("CoreUObject");
		PublicDependencyModuleNames.Add("Engine");
		PublicDependencyModuleNames.Add("InputCore");
		PublicDependencyModuleNames.Add("Paper2D");
		PublicDependencyModuleNames.Add("UMG");
		PublicDependencyModuleNames.Add("OnlineSubsystem");
		PublicDependencyModuleNames.Add("OnlineSubsystemSteam");
		PublicDependencyModuleNames.Add("GameplayCameras");
		PublicDependencyModuleNames.Add("AIModule");
		PublicDependencyModuleNames.Add("GameplayTasks");

		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		//PrivateDependencyModuleNames.AddRange(new string[] { "Paper2D" });


	}
}
