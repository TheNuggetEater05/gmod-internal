#pragma once

#ifndef INTERFACEMANAGER_H
#define INTERFACEMANAGER_H

#include <Includes.h>
#include <Singleton.h>

class Module;

struct Interface
{
	using CreateFn = void* (*)();
	CreateFn m_pCreateFn;
	const char* m_pName;
	Interface* m_pNext;
};

class InterfaceManager : public Singleton<InterfaceManager>
{
	friend class Singleton<InterfaceManager>;
public:
	bool Init();
	void Shutdown();

	template<typename T>
	T* GetI(const std::string& modName, const std::string& interfaceName)
	{
		return reinterpret_cast<T*>(GetInterface(modName, interfaceName));
	}

	void Dump(const std::string& modName);

private:
	void* GetInterface(const std::string& modName, const std::string& interfaceName);

private:
	Module* m_Global;
	Interface* m_First;
};

#endif // !INTERFACEMANAGER_H
