#include "NetvarManager.h"

#include "../../Global.h"

namespace NVManager
{
	void Dump(RecvTable* pTable, uintptr_t offset)
	{
		for (int i = 0; i < pTable->m_nProps; i++)
		{
			RecvProp* prop = &pTable->m_pProps[i];
			const char* name = prop->m_pVarName;

			if (isdigit(name[0]))
				return;

			//G::pOutput->Log("%s", name);

			if (strcmp(prop->m_pVarName, "baseclass") == 0)
			{
				G::pOutput->Log(" - %s", prop->m_pDataTable->m_pNetTableName);
				Dump(prop->m_pDataTable, prop->m_Offset);
				continue;
			}

			G::pOutput->Log("\t%s : %x", prop->m_pVarName, prop->m_Offset);
		}
	}

	void DumpClass(const std::string& name)
	{
		for (ClientClass* pClientClass = I::Client->GetAllClasses(); pClientClass; pClientClass = pClientClass->m_pNext)
		{
			if (strcmp(pClientClass->m_pNetworkName, name.c_str()) == 0)
			{
				return Dump(pClientClass->m_pRecvTable);
			}
		}
	}
}