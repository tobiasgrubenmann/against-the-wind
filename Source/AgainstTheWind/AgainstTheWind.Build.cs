// Copyright 2023 Tobias Grubenmann.

using UnrealBuildTool;

public class AgainstTheWind : ModuleRules
{
	public AgainstTheWind(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });
	}
}
