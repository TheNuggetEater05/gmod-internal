#pragma once

#ifndef INTERFACEMANAGER_H
#define INTERFACEMANAGER_H

#include "../../Includes.h"

namespace IManagers
{
	class InterfaceManager;

	extern InterfaceManager* Client;
	extern InterfaceManager* Engine;

	extern void Init();
	extern void Cleanup();

	struct InterfaceNode
	{
		using fnCreateFn = void* (*)();
		fnCreateFn m_pCreateFn;
		const char* m_pName;
		InterfaceNode* m_pNext;
	};

	class InterfaceManager
	{
	private:
		void* _GetRaw(const std::string& name);

	public:
		InterfaceManager(const std::string& module);

		template <typename Interface>
		Interface* Get(const std::string& name)
		{
			return reinterpret_cast<Interface*>(_GetRaw(name));
		}

		void DumpAll();

	private:
		HMODULE m_Base;
		std::string m_Name;
		InterfaceNode* m_Head;
	};
}

#endif