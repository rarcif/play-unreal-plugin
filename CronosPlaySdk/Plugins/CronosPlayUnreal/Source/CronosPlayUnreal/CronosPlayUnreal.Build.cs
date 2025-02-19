using System;
using System.IO;
using UnrealBuildTool;

public class CronosPlayUnreal : ModuleRules
{
	public CronosPlayUnreal(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		CppStandard = CppStandardVersion.Cpp17;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);

		if (UnrealTargetPlatform.Win64 == Target.Platform)
        {
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Private/cronosplay/lib/Win64", "play_cpp_sdk.dll.lib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Private/cronosplay/lib/Win64", "libcxxbridge1.a"));

        }
        else if (UnrealTargetPlatform.Mac == Target.Platform)
        {
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Private/cronosplay/lib/Mac", "libplay_cpp_sdk.dylib"));
            PublicAdditionalLibraries.Add(Path.Combine(ModuleDirectory, "Private/cronosplay/lib/Mac", "libcxxbridge1.a"));
        }	

		// load dll 
        if (Target.Platform == UnrealTargetPlatform.Win64)
        {
            PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "Private", "cronosplay","lib","Win64", "play_cpp_sdk.dll"));
            RuntimeDependencies.Add("$(PluginDir)/Source/CronosPlayUnreal/Private/cronosplay/lib/Win64/play_cpp_sdk.dll");
        }
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {
        	PublicDelayLoadDLLs.Add(Path.Combine(ModuleDirectory, "Private", "cronosplay","lib","Mac", "libplay_cpp_sdk.dylib"));
            RuntimeDependencies.Add("$(PluginDir)/Source/CronosPlayUnreal/Private/cronosplay/lib/Mac/libplay_cpp_sdk.dylib");
        }
		
	}
}
