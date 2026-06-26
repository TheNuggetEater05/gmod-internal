#pragma once

#ifndef SETTINGS_H
#define SETTINGS_H

#include "types/Color.h"
#include <string>

struct Settings
{
	struct Visuals
	{
		struct Watermark
		{
			bool enabled = true;
			Color color = {1.0f, 1.0f, 0.0f};
			int size = 21;
		} Watermark;

		struct ESP
		{
			bool enabled = false;
			Color color = { 1.0f, 0.0f, 0.0f };
		} ESP;
	} Visuals;
};

struct GameInfo
{
	int FPS = 0;
	std::string ServerName = "";
};

inline Settings g_Settings;
inline GameInfo g_GameInfo;

#endif // !SETTINGS_H
