#pragma once

#ifndef GLOBAL_H
#define GLOBAL_H

#define WIN32_LEAN_AND_MEAN

// Commonly used includes
#include "Includes.h"

#include "utility/Logger.h"
#include "utility/Memory.h"

#include "sdk/SDK.h"

namespace G
{
	// Global function declarations
	extern inline const bool InitializeModule(HMODULE hModule);
	extern inline const void ExitModule();
	extern const void ExitModule(const char* fmt, ...);
	extern const void ExitModule(const char* fmt, va_list args);

	// Global variables & references
	extern inline const std::string logPrefix;

	extern HMODULE hMod;
	extern Logger* pOutput;
}

namespace I
{
	extern void* EntityList;
	extern void* Client;
}

#endif