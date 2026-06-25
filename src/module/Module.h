#pragma once
#ifndef MODULE_H
#define MODULE_H

#include <Includes.h>
#include <Singleton.h>

class Logger;
class HookManager;
class Renderer;

class Module : public Singleton<Module>
{
	friend class Singleton<Module>;
public:
	void Start(HMODULE hMod);
	void Update();
	void Kill(const char* format = "", ...);

	void Log(const char* format, ...);

public:
	Logger* pLogger;
	HookManager* pHookManager;
	Renderer* pRenderer;

private:
	bool m_Initialized = false;
	HMODULE m_hModule = nullptr;


private:
	bool Init();
};

#endif // !MODULE_H
