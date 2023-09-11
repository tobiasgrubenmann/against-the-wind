// Copyright 2023 Tobias Grubenmann.

using UnrealBuildTool;

public class WindPhysicsTest : ModuleRules
{
	public WindPhysicsTest(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] { "WindPhysics" });
	}
}
