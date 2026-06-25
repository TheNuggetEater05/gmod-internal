#include "HookManager.h"

#include "../Module.h"
#include "../logger/Logger.h"

// hooks
#include "hooks/D3D/D3D.h"

#include <minhook/MinHook.h>
#include <Memory.h>

bool HookManager::Init()
{
	m_Global = &Module::Get();

	if (MH_Initialize())
	{
		m_Global->pLogger->Log(LOG_ERROR, "HookManager: Failed to initialize");
		return false;
	}

	if (!D3D::Init())
	{
		m_Global->pLogger->Log(LOG_ERROR, "HookManager: Failed to initialize D3D hook");
		return false;
	}

	{
		void** vtD3D = Memory::GetVTable(D3D::pDeviceTemp);
		SetHook("D3DEndScene", vtD3D[42], &D3D::hkEndScene, reinterpret_cast<void**>(&D3D::oEndScene));
		SetHook("D3DReset", vtD3D[16], &D3D::hkReset, reinterpret_cast<void**>(&D3D::oReset));
	}

	EnableHooks();

	m_Global->pLogger->Log(LOG_SUCCESS, "HookManager: Initialized");
	return true;
}

void HookManager::Shutdown()
{
	MH_DisableHook(MH_ALL_HOOKS);
	MH_Uninitialize();

	m_Global->pLogger->Log(LOG_SUCCESS, "HookManager: Shutdown");
}

bool HookManager::SetHook(const std::string& name, void* target, void* detour, void** original)
{
	if (MH_STATUS status = MH_CreateHook(target, detour, original))
	{
		m_Global->pLogger->Log(LOG_ERROR, "HookManager: Failed to set hook - %s, MH_STATUS = %i", name.c_str(), status);
		return false;
	}

	m_Hooks.push_back(
		{
			name,
			target,
			detour,
			original
		});

	m_Global->pLogger->Log(LOG_SUCCESS, "HookManager: Set hook - %s", name.c_str());
	return true;
}

bool HookManager::EnableHooks()
{
	for (const Hook& hook : m_Hooks)
	{
		if (MH_STATUS status = MH_EnableHook(hook.Target))
		{
			m_Global->pLogger->Log(LOG_ERROR, "HookManager: Failed to enable hook - %s, MH_STATUS = %i", hook.Name, status);
			return false;
		}
	}

	return true;
}