// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DreamateTestTaskEditorTarget : TargetRules
{
	public DreamateTestTaskEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[] { "DreamateTestTask" } );
	}
}
