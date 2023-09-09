// Copyright 2023 Tobias Grubenmann.

using UnrealBuildTool;
using System.Collections.Generic;

public class AgainstTheWindTarget : TargetRules
{
	public AgainstTheWindTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_3;
		ExtraModuleNames.Add("AgainstTheWind");
		ExtraModuleNames.Add("WindPhysics");
	}
}
