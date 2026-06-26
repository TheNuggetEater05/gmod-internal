#pragma once

#ifndef IVDEBUGOVERLAY_H
#define IVDEBUGOVERLAY_H

#include "../types/Vector.h"

class IVDebugOverlay
{
public:
	Vec2 WorldToScreen(const Vec3& point);
};

#endif // !IVDEBUGOVERLAY_H
