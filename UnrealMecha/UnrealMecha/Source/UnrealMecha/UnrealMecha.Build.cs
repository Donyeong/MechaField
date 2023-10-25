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

		// ���̺귯�� ��� ����
		string LibrariesPath = "D:\\Works\\Projects\\MechaField\\GameModule\\CppGameModule\\DModules";

		// ���̺귯�� �߰�
		
		PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "DGameLogic\\DGameLogic.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "DGameLogic\\DNetwork.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "DGameLogic\\DUtil.lib"));
		PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "DGameLogic\\DNetwork.lib"));
		

		//string BaseDirectory = Path.GetFullPath(Path.Combine(ModuleDirectory, "..", "ThirdParty"));
		//string DLLName = "DUtil.dll";

		// �̰��� ��Ÿ�� �߿� DLL�� �ε��ϱ� ���� ���Դϴ�.
		//RuntimeDependencies.Add(Path.Combine(BaseDirectory, DLLName));

		// �̰��� ��Ű¡ ���߿� DLL�� ������Ʈ�� ���̳ʸ� ������ �����ϱ� ���� ���Դϴ�.
		//RuntimeDependencies.Add("$(TargetOutputDir)/" + DLLName, Path.Combine(BaseDirectory, DLLName));




		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
