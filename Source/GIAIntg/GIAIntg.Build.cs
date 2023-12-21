// Copyright (C) 2023 owoDra

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
                "Core",
                "CoreUObject",
                "Engine",
                "ModularGameplay",
                "GameplayAbilities",
            }
        );


        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "GFCore",
                "GIExt",
                "GAExt",
            }
        );
    }
}
