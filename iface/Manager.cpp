#include "Manager.h"
#include "../Global.h"

namespace ifacemanager
{
	IFaceManager::IFaceManager(const std::string& moduleName) : m_Name(moduleName), m_Base(0), m_FirstNode(0)
	{
		uint8_t* pCreateInterface;	// first byte of CreateInterface
		uint8_t* pInstruction;		// first byte of wanted instruction
		uint32_t displacement;		// 3 bytes into instruction

		m_Base = GetModuleHandleA(moduleName.c_str());
		if (!m_Base)
			glb::Exit("Failed to get module base of %s", moduleName.c_str());

		pCreateInterface = reinterpret_cast<uint8_t*>(GetProcAddress(m_Base, "CreateInterface"));
		if (!pCreateInterface)
			glb::Exit("Failed to get CreateInterface in %s", moduleName.c_str());

		m_FirstNode = Memory::ExtractAddressFromFunc<IFaceNode>(pCreateInterface, 15, 3);
		if (!m_FirstNode)
			glb::Exit("Failed to get first IFaceNode in %s", moduleName.c_str());
	}

	void* IFaceManager::Get(const std::string& name)
	{
		if (m_FirstNode)
			for (IFaceNode* pNode = m_FirstNode; pNode; pNode = pNode->m_pNext)
				if (std::string(pNode->m_pName).find(name) != std::string::npos)
					return pNode->m_pCreateFn();

		glb::Exit("Failed to get Interface %s in %s", name.c_str(), m_Name.c_str());
		return nullptr;
	}

	void IFaceManager::Dump()
	{
		if (m_FirstNode)
			for (IFaceNode* pNode = m_FirstNode; pNode; pNode = pNode->m_pNext)
				glb::Output->Log("[%s] interface: %s", m_Name.c_str(), pNode->m_pName);
	}
}