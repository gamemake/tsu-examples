using UnrealBuildTool;

public class TsuShell : ModuleRules
{
	public TsuShell(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(
			new string[] {
				"Core",
				"V8",
				"libWebSockets"
			});
	}
}
