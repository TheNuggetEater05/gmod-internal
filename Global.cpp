#include "Global.h"

namespace glb
{
	HMODULE hMod = nullptr;
	Logger* Output = nullptr;

	namespace iface
	{
		std::unique_ptr<ifacemanager::IFaceManager> pClient;
		std::unique_ptr<ifacemanager::IFaceManager> pEngine;

		IBaseClient* pBaseClientDll;
		IClientEntityList* pClientEntityList;
	}

	void Init()
	{
		Output = &Logger::Get();
		Output->Init();
		Output->SetPrefix("gmod-internal");
		Output->Log("Initializing globals");

		iface::pClient = std::make_unique<ifacemanager::IFaceManager>("client.dll");
		iface::pEngine = std::make_unique<ifacemanager::IFaceManager>("engine.dll");

		iface::pBaseClientDll = iface::pClient->Get<IBaseClient>("VClient0");
		iface::pClientEntityList = iface::pClient->Get<IClientEntityList>("VClientEntityList0");

		Output->Log(LOG_SUCCESS, "Initialized globals");
	}

	void Exit()
	{
		Output->Log("Unloading gmod-internal");

		Output->Log(LOG_SUCCESS, "You can now close this window");

		FreeConsole();
		FreeLibraryAndExitThread(hMod, 0);
	}

	void Exit(const char* fmt, ...)
	{
		va_list args;
		va_start(args, fmt);

		Output->Log(LOG_ERROR, fmt, args);

		va_end(args);

		Exit();
	}
}