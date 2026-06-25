#include "Module.h"

#include "logger/Logger.h"
#include "hookmanager/HookManager.h"
#include "renderer/Renderer.h"

#include <imgui/imgui.h>

#include "Settings.h"

void Module::Start(HMODULE hModule)
{
	if (m_Initialized)
		return;

	m_hModule = hModule;

	if (!Init())
		Kill("Failed to initialize module");
}

void Module::Update()
{
	if (!ImGui::GetCurrentContext())
		return;

	g_GameInfo.FPS = ImGui::GetIO().Framerate;
}

// Private
bool Module::Init()
{
	// Initialize systems
	pLogger = &Logger::Get();
	pLogger->Init();
	pLogger->SetPrefix("GMOD-INTERNAL-V2");

	// Initialize hooks
	pHookManager = &HookManager::Get();
	pHookManager->Init();

	// Renderer is now initialized in D3D.cpp EndScene hook
	pRenderer = &Renderer::Get();
	//pRenderer->Init();

	pLogger->Log(LOG_SUCCESS, "Module initialized");
	m_Initialized = true;
}

void Module::Kill(const char* format, ...)
{
	if (*format)
	{
		va_list args;
		va_start(args, format);
		pLogger->Log(format, args);
		va_end(args);
	}

	pLogger->Log("Killing module");

	pHookManager->Shutdown();
	pRenderer->Shutdown();

	pLogger->Log(LOG_SUCCESS, "Module unloaded");

	pLogger->Destroy();
	FreeLibraryAndExitThread(m_hModule, 0);
}
