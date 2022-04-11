// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DreamateTestTask : ModuleRules
{
	public DreamateTestTask(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			"UMG", "AIModule", "EnhancedInput", "GameplayAbilities", "GameplayTags",
			"GameplayTasks", "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "MaterialEditor"
		});
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore"  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
