// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProjetSpecial : ModuleRules
{
	public ProjetSpecial(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"ProjetSpecial",
			"ProjetSpecial/Variant_Platforming",
			"ProjetSpecial/Variant_Platforming/Animation",
			"ProjetSpecial/Variant_Combat",
			"ProjetSpecial/Variant_Combat/AI",
			"ProjetSpecial/Variant_Combat/Animation",
			"ProjetSpecial/Variant_Combat/Gameplay",
			"ProjetSpecial/Variant_Combat/Interfaces",
			"ProjetSpecial/Variant_Combat/UI",
			"ProjetSpecial/Variant_SideScrolling",
			"ProjetSpecial/Variant_SideScrolling/AI",
			"ProjetSpecial/Variant_SideScrolling/Gameplay",
			"ProjetSpecial/Variant_SideScrolling/Interfaces",
			"ProjetSpecial/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
