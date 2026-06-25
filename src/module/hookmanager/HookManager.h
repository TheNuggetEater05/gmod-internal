#pragma once

#ifndef HOOKMANAGER_H
#define HOOKMANAGER_H

#include <Includes.h>
#include <Singleton.h>

class Module;

struct Hook
{
	std::string Name;
	void* Target;
	void* Detour;
	void** Original;
};

class HookManager : public Singleton<HookManager>
{
	friend class Singleton<HookManager>;
public:
	bool Init();
	void Shutdown();

private:
	Module* m_Global;
	std::vector<Hook> m_Hooks{};

	bool SetHook(const std::string& name, void* target, void* detour, void** original);
	bool EnableHooks();
};

#endif // !HOOKMANAGER_H
