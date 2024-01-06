// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DebugExtensions : ModuleRules
{
	public DebugExtensions(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		if (Target.Type == TargetType.Editor)
		{
			PublicIncludePaths.AddRange(new string[] { });
			PrivateIncludePaths.AddRange(new string[] { });
			DynamicallyLoadedModuleNames.AddRange(new string[] { });
		
			PublicDependencyModuleNames.AddRange(
				new string[]
				{
					"Core",
					"CoreUObject",
					"Engine",
					"InputCore",
					"Slate",
					"SlateCore",
					"MeshDescription",
					"StaticMeshDescription",
					"Kismet"
				}
			);
		
			PrivateDependencyModuleNames.AddRange(
				new string[]
				{
				}
			);
		}
		
		PublicIncludePaths.AddRange(new string[] { });
		PrivateIncludePaths.AddRange(new string[] { });
		DynamicallyLoadedModuleNames.AddRange(new string[] { });
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"InputCore",
				"Slate",
				"SlateCore",
				"MeshDescription",
				"StaticMeshDescription"
			}
		);
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
			}
		);
	}
}
