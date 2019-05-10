using UnrealBuildTool;

public class TsuShellTarget : TargetRules
{
	public TsuShellTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Program;
		LinkType = TargetLinkType.Modular;
		LaunchModuleName = "TsuShell";

		// DsymExporter doesn't ever compile with the engine linked in
		bCompileAgainstEngine = false;

		// DsymExporter has no exports, so no need to verify that a .lib and .exp file was emitted by the linker.
		bHasExports = false;

        bCompileAgainstCoreUObject = false;

		// Do NOT produce additional console app exe
		bIsBuildingConsoleApplication = true;

		// Currently we force Lean and Mean mode
		bBuildDeveloperTools = false;

		// ShaderCompileWorker isn't localized, so doesn't need ICU
		bCompileICU = false;

		// Currently this app is not linking against the engine, so we'll compile out references from Core to the rest of the engine
		bCompileAgainstEngine = false;
		bCompileAgainstCoreUObject = false;
		bBuildWithEditorOnlyData = true;
		bCompileCEF3 = false;

		// Never use malloc profiling in ShaderCompileWorker.
		bUseMallocProfiler = false;

		// Force all shader formats to be built and included.
        bForceBuildShaderFormats = true;

		// ShaderCompileWorker is a console application, not a Windows app (sets entry point to main(), instead of WinMain())
		bIsBuildingConsoleApplication = true;
	}
}
