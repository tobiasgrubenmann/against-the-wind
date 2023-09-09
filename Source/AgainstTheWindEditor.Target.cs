// Copyright 2023 Tobias Grubenmann.

using UnrealBuildTool;
using System.Collections.Generic;

public class AgainstTheWindEditorTarget : TargetRules
{
	public AgainstTheWindEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_3;
		ExtraModuleNames.Add("AgainstTheWind");
		ExtraModuleNames.Add("WindPhysics");
	}
}
