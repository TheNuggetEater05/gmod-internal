#pragma once

#ifndef GLOBAL_H
#define GLOBAL_H

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>
#include <cstdint>

#include "util/Logger.h"
#include "util/Memory.h"

#include "iface/Manager.h"
#include "iface/valve/IBaseClient.h"
#include "iface/valve/IClientEntityList.h"

namespace glb
{
	extern HMODULE hMod;
	extern Logger* Output;

	// Interface managers

	namespace iface
	{
		extern std::unique_ptr<ifacemanager::IFaceManager> pClient;
		extern std::unique_ptr<ifacemanager::IFaceManager> pEngine;

		// Interfaces
		extern IBaseClient* pBaseClientDll;
		extern IClientEntityList* pClientEntityList;
	}

	void Init();

	void Exit();
	void Exit(const char* fmt, ...);
}

#endif