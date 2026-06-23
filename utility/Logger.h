#pragma once

#ifndef LOGGER_H
#define LOGGER_H

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <string>
#include <iostream>

#include "Singleton.h"

enum LOG_LEVELS
{
	LOG_INFO = 0,
	LOG_SUCCESS,
	LOG_WARN,
	LOG_ERROR,
};

class Logger : public Singleton<Logger>
{
	friend class Singleton<Logger>;

public:
	void Init()
	{
		if (m_Initialized)
			return;

		makeAnsiSupportedConsole();

		disableClose();

		m_Initialized = true;
	}

	inline void Destroy()
	{
		enableClose();
		FreeConsole();
	}

	/*
	* UNIMPLEMENTED
	* Adds feature to context menu
	*/
	void AddFeature(const std::string& name, void* feature)
	{
	}

	/*
	* Set's prefix of every log made
	* ex: [prefix] [level] ...
	*/
	void SetPrefix(const std::string& prefix = "LOG")
	{
		m_Prefix = prefix;
	}

	void Log(int level, const char* fmt, va_list args)
	{
		std::string logPrefix = MAGENTA + "[" + RESET + BOLD + m_Prefix + RESET + MAGENTA + "]" + RESET;

		// Choose which formatting options depending on level
		switch (level)
		{
		case LOG_INFO:
			logPrefix += BRIGHT_BLACK + BOLD + "[I]" + RESET;
			break;
		case LOG_SUCCESS:
			logPrefix += BRIGHT_GREEN + BOLD + "[+]" + RESET;
			break;
		case LOG_WARN:
			logPrefix += BRIGHT_YELLOW + BOLD + "[~]" + RESET;
			break;
		case LOG_ERROR:
			logPrefix += BRIGHT_RED + BOLD + "[!]" + RESET;
		}

		printf("%s ~ ", logPrefix.c_str());
		vprintf(fmt, args);
		std::printf("\n");
	}

	// If no level then print as LOG_INFO
	void Log(const char* fmt, ...)
	{
		va_list args;

		va_start(args, fmt);
		Log(LOG_INFO, fmt, args);

		va_end(args);
	}

	void Log(int level, const char* fmt, ...)
	{
		va_list args;

		va_start(args, fmt);

		Log(level, fmt, args);

		va_end(args);
	}

private:
	bool m_Initialized = false;
	std::string m_Prefix;
	HMENU hMenu = nullptr;
	HWND hWnd;

private:

	void makeAnsiSupportedConsole()
	{
		FILE* fConsole;
		HANDLE hOut = nullptr;
		DWORD mode = 0;

		// Create the console
		AllocConsole();
		freopen_s(&fConsole, "CONOUT$", "w", stdout);
		freopen_s(&fConsole, "CONOUT$", "w", stderr);

		SetConsoleOutputCP(CP_UTF8);
		SetConsoleCP(CP_UTF8);

		hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleMode(hOut, &mode);
		mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
		SetConsoleMode(hOut, mode);

		hWnd = GetConsoleWindow();
		hMenu = GetSystemMenu(hWnd, FALSE);
	}

	void disableClose()
	{
		EnableMenuItem(hMenu, SC_CLOSE, MF_BYCOMMAND | MF_GRAYED);

		DrawMenuBar(hWnd);
	}

	void enableClose()
	{
		EnableMenuItem(hMenu, SC_CLOSE, MF_BYCOMMAND | MF_ENABLED);

		DrawMenuBar(hWnd);
	}

	// Putting these down here so they dont hide everything else
private:
	const std::string RESET = "\033[0m";
	const std::string BOLD = "\033[1m";
	const std::string DIM = "\033[2m";
	const std::string ITALIC = "\033[3m";
	const std::string UNDERLINE = "\033[4m";
	const std::string BLINK = "\033[5m";
	const std::string REVERSE = "\033[7m";
	const std::string HIDDEN = "\033[8m";

	const std::string BLACK = "\033[30m";
	const std::string RED = "\033[31m";
	const std::string GREEN = "\033[32m";
	const std::string YELLOW = "\033[33m";
	const std::string BLUE = "\033[34m";
	const std::string MAGENTA = "\033[35m";
	const std::string CYAN = "\033[36m";
	const std::string WHITE = "\033[37m";

	const std::string BRIGHT_BLACK = "\033[90m";
	const std::string BRIGHT_RED = "\033[91m";
	const std::string BRIGHT_GREEN = "\033[92m";
	const std::string BRIGHT_YELLOW = "\033[93m";
	const std::string BRIGHT_BLUE = "\033[94m";
	const std::string BRIGHT_MAGENTA = "\033[95m";
	const std::string BRIGHT_CYAN = "\033[96m";
	const std::string BRIGHT_WHITE = "\033[97m";

	const std::string BG_BLACK = "\033[40m";
	const std::string BG_RED = "\033[41m";
	const std::string BG_GREEN = "\033[42m";
	const std::string BG_YELLOW = "\033[43m";
	const std::string BG_BLUE = "\033[44m";
	const std::string BG_MAGENTA = "\033[45m";
	const std::string BG_CYAN = "\033[46m";
	const std::string BG_WHITE = "\033[47m";

	const std::string BG_BRIGHT_BLACK = "\033[100m";
	const std::string BG_BRIGHT_RED = "\033[101m";
	const std::string BG_BRIGHT_GREEN = "\033[102m";
	const std::string BG_BRIGHT_YELLOW = "\033[103m";
	const std::string BG_BRIGHT_BLUE = "\033[104m";
	const std::string BG_BRIGHT_MAGENTA = "\033[105m";
	const std::string BG_BRIGHT_CYAN = "\033[106m";
	const std::string BG_BRIGHT_WHITE = "\033[107m";
};

#endif