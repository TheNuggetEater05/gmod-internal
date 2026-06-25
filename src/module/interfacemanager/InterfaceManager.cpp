#include "InterfaceManager.h"

#include "../Module.h"
#include "../logger/Logger.h"
#include <Memory.h>

bool InterfaceManager::Init()
{
	m_Global = &Module::Get();

	//m_First = Memory::ExtractAddressFromFunc(reinterpret_cast<uint8_t*>(GetProcAddress()), 15, 3)

	// Loop through all interfaces and add them to m_Interfaces


	m_Global->pLogger->Log(LOG_SUCCESS, "InterfaceManager: Initialized");
	return true;
}

void InterfaceManager::Shutdown()
{

	m_Global->pLogger->Log(LOG_SUCCESS, "InterfaceManager: Shutdown");
}

void InterfaceManager::Dump(const std::string& modName)
{
	HMODULE base;
	Interface* head;

	base = GetModuleHandle(modName.c_str());

	if (!base)
	{
		m_Global->pLogger->Log(LOG_ERROR, "InterfaceManager: Failed to get %s's base address", modName.c_str());
		return;
	}

	head = Memory::ExtractAddressFromFunc<Interface>(reinterpret_cast<uint8_t*>(GetProcAddress(base, "CreateInterface")), 15, 3);

	if (head)
		for (Interface* pNode = head; pNode; pNode = pNode->m_pNext)
			m_Global->pLogger->Log("[%s] - %s", modName.c_str(), pNode->m_pName);
}

void* InterfaceManager::GetInterface(const std::string& modName, const std::string& interfaceName)
{
	HMODULE base;
	Interface* head;

	base = GetModuleHandle(modName.c_str());

	if (!base)
	{
		m_Global->pLogger->Log(LOG_ERROR, "InterfaceManager: Failed to get %s's base address", modName.c_str());
		return nullptr;
	}

	head = Memory::ExtractAddressFromFunc<Interface>(reinterpret_cast<uint8_t*>(GetProcAddress(base, "CreateInterface")), 15, 3);
	if (!head)
	{
		m_Global->pLogger->Log(LOG_ERROR, "InterfaceManager: Failed to get %s from %s", interfaceName.c_str(), modName.c_str());
		return nullptr;
	}
	if (head)
		for (Interface* pNode = head; pNode; pNode = pNode->m_pNext)
			if (std::string(pNode->m_pName).find(interfaceName) != std::string::npos)
				return pNode->m_pCreateFn();

	return nullptr;
}