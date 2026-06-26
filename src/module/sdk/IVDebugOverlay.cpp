#include "IVDebugOverlay.h"

#include <Memory.h>

#include "../logger/Logger.h"

Vec2 IVDebugOverlay::WorldToScreen(const Vec3& point)
{
	using fn = int(*)(void*, const Vec3&, Vec3&);
	
	Vec3 screen(0.0f);

	if (Memory::GetVFunc<fn>(this, 10)(this, point, screen))
		return Vec2(0.0f);
	return Vec2(screen.x, screen.y);
}
