// Copyright Epic Games, Inc. All Rights Reserved.

using System.Diagnostics;
using System.IO;
using UnrealBuildTool;
using UnrealBuildTool.Rules;

public class UnrealMecha : ModuleRules
{
	public UnrealMecha(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });
		
		PublicIncludePaths.AddRange(new string[] { "D:\\Works\\Projects\\MechaField\\GameModule\\CppGameModule" });

		// 라이브러리 경로 설정
		string LibrariesPath = "D:\\Works\\Projects\\MechaField\\GameModule\\CppGameModule\\DModules";

		// 라이브러리 추가
		
		PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "DGameLogic\\DGameLogic.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "DGameLogic\\DNetwork.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "DGameLogic\\DUtil.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "DGameLogic\\DNetwork.lib"));
		

		//string BaseDirectory = Path.GetFullPath(Path.Combine(ModuleDirectory, "..", "ThirdParty"));
		//string DLLName = "DUtil.dll";

		// 이것은 런타임 중에 DLL을 로드하기 위한 것입니다.
		//RuntimeDependencies.Add(Path.Combine(BaseDirectory, DLLName));

		// 이것은 패키징 도중에 DLL을 프로젝트의 바이너리 폴더로 복사하기 위한 것입니다.
		//RuntimeDependencies.Add("$(TargetOutputDir)/" + DLLName, Path.Combine(BaseDirectory, DLLName));




		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
