#pragma once

#ifndef IFACE_MANAGER_H
#define IFACE_MANAGER_H

#include <string>
#include <Windows.h>

namespace ifacemanager
{
	class IFaceManager;
	struct IFaceNode;

	struct IFaceNode
	{
		using fnCreateFn = void* (*)();
		fnCreateFn m_pCreateFn;
		const char* m_pName;
		IFaceNode* m_pNext;
	};

	class IFaceManager
	{
	public:
		IFaceManager(const std::string& moduleName);

		void* Get(const std::string& name);

		template <typename T>
		T* Get(const std::string name)
		{
			return reinterpret_cast<T*>(Get(name));
		}

		void Dump();

	private:
		std::string m_Name;
		HMODULE m_Base;

		IFaceNode* m_FirstNode;
	};
}

#endif