#include "InterfaceManager.h"

#include "../../Global.h"

namespace IManagers
{
	extern InterfaceManager* Client = nullptr;
	extern InterfaceManager* Engine = nullptr;

	void Init()
	{
		Client = new InterfaceManager("client.dll");
		Engine = new InterfaceManager("engine.dll");
	}

	void Cleanup()
	{
		delete Client;
		delete Engine;
	}

	InterfaceManager::InterfaceManager(const std::string& module) : m_Base(0), m_Head(nullptr), m_Name(module)
	{
		m_Base = GetModuleHandleA(module.c_str());
		if (!m_Base)
			G::ExitModule("InterfaceManager: Failed to get handle to %s", module.c_str());

		uint8_t* pCreateInterface = reinterpret_cast<uint8_t*>(GetProcAddress(m_Base, "CreateInterface"));

		m_Head = Memory::ExtractAddressFromFunc<InterfaceNode>(pCreateInterface, 15, 3);
		if (!m_Head)
			G::ExitModule("InterfaceManager: Failed to get first interface node in %s", module.c_str());
	}

	void* InterfaceManager::_GetRaw(const std::string& name)
	{
		if (m_Head)
		{
			for (InterfaceNode* pNode = m_Head; pNode; pNode = pNode->m_pNext)
			{
				if (std::string(pNode->m_pName).find(name) != std::string::npos)
				{
					return pNode->m_pCreateFn();
				}
			}
		}
		return nullptr;
	}

	void InterfaceManager::DumpAll()
	{
		if (m_Head)
		{
			for (InterfaceNode* pNode = m_Head; pNode; pNode = pNode->m_pNext)
			{
				G::pOutput->Log("InterfaceManager: [%s] - %s @ %p", m_Name.c_str(), pNode->m_pName, pNode->m_pCreateFn());
			}
		}
	}
}
