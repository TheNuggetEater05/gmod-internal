#include "Global.h"

#include "sdk/interfaces/InterfaceManager.h"

namespace I
{
	IClientEntityList* EntityList = nullptr;
	IClientBaseDLL* Client = nullptr;

	void Init()
	{
		EntityList = IManagers::Client->Get<IClientEntityList>("VClientEntityList0");
		Client = IManagers::Client->Get<IClientBaseDLL>("VClient0");
	}
}

namespace G
{
	// Global variable & references declarations
	inline const std::string logPrefix = "GMOD-INTERNAL";

	HMODULE hMod = nullptr;
	Logger* pOutput = nullptr;

	// Global function definitions
	inline const bool InitializeModule(HMODULE hModule)
	{
		// Fill our variables and references
		hMod = hModule;

		pOutput = &Logger::Get();

		// Initialize systems
		pOutput->Init();
		pOutput->SetPrefix(logPrefix);

		IManagers::Init();
		I::Init();

		return true;
	}

	inline const void ExitModule()
	{
		pOutput->Log("Cleaning up and unloading...");

		// Any clean ups here
		IManagers::Cleanup();

		pOutput->Log(LOG_SUCCESS, "Finished cleaning up");
		pOutput->Log("You can now close this window");

		pOutput->Destroy();
		FreeLibraryAndExitThread(hMod, 0);
	}
	const void ExitModule(const char* fmt, va_list args)
	{
		pOutput->Log(LOG_ERROR, fmt, args);

		ExitModule();
	}
	const void ExitModule(const char* fmt, ...)
	{
		va_list args;
		va_start(args, fmt);

		ExitModule(fmt, args);

		va_end(args);
	}
}