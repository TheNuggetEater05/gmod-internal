#include "NetvarManager.h"

#include <ctype.h>
#include <format>

#include "../sdk/IBaseClientDLL.h"
#include "../interfacemanager/InterfaceManager.h"
#include "../logger/Logger.h"

#include <fstream>

void NetvarManager::Init()
{
	std::ofstream file("C:\\Users\\Public\\netvars.txt");

	m_BaseClient = InterfaceManager::Get().GetI<IBaseClientDLL>("client.dll", "VClient0");
	for (ClientClass* clientClass = m_BaseClient->GetAllClasses(); clientClass; clientClass = clientClass->m_pNext)
		if (clientClass->m_pRecvTable)
			Dump(std::string(clientClass->m_pNetworkName), clientClass->m_pRecvTable, 0, &file);

	file.close();
	Logger::Get().Log(LOG_SUCCESS, "Renderer: Initialized");
}

void NetvarManager::PrintNetvar(const std::string& name)
{
	Logger::Get().Log("%s : %x", name.c_str(), netvars[fnv::Hash(name.c_str())]);
}

void NetvarManager::Dump(const std::string& baseclass, RecvTable* table, std::uint32_t offset, std::ofstream* file)
{
	for (int i = 0; i < table->m_nProps; i++)
	{
		const RecvProp* prop = &table->m_pProps[i];

		if (!prop || isdigit(prop->m_pVarName[0]))
			continue;

		if (fnv::Hash(prop->m_pVarName) == fnv::HashConst("baseclass"))
			continue;

		if (prop->m_pDataTable && prop->m_pDataTable->m_pNetTableName[0] == 'D')
			Dump(baseclass.c_str(), prop->m_pDataTable, offset + prop->m_Offset, file);

		const auto name = std::format("{}->{}", baseclass, prop->m_pVarName);

		*file << name.c_str() << " : " << std::hex << prop->m_Offset + offset << std::dec << "\n";
		netvars[fnv::Hash(name.c_str())] = offset + prop->m_Offset;
	}
}
