#pragma once

#ifndef SETTINGS_H
#define SETTINGS_H

#include "types/Color.h"

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
	} Visuals;
};

inline Settings g_Settings;

#endif // !SETTINGS_H
