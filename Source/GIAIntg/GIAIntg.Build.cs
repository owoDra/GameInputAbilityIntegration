// Copyright (C) 2024 owoDra

using UnrealBuildTool;

public class GIAIntg : ModuleRules
{
	public GIAIntg(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicIncludePaths.AddRange(
            new string[]
            {
                ModuleDirectory,
                ModuleDirectory + "/GIAIntg",
            }
        );


        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core", "CoreUObject", "Engine",

                "GameplayAbilities",
            }
        );


        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "GEInput", "GAExt",
            }
        );
    }
}
