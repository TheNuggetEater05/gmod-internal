#include "Watermark.h"
#include "../../../renderer/Renderer.h"

#include "../../../types/Vector.h"
#include "../../../types/Color.h"

#include "../../../Settings.h"

void Watermark::Render()
{
	Renderer::Get().DrawText("GMOD INTERNAL REWRITE | " + std::to_string(g_GameInfo.FPS) + " FPS", {5, 5}, g_Settings.Visuals.Watermark.color, true, (float)g_Settings.Visuals.Watermark.size, Renderer::Get().GetFont("ProggyForever"));

	Renderer::Get().DrawRect(Vec2(100, 100), Vec2(200, 300), Color(1.0f, 1.0f, 1.0f, 1.0f), 1.0f, true, false, 20.0f);

	Renderer::Get().DrawCircle(Vec2(200, 300), Color(1.0f, 0.0f, 1.0f, 1.0f), 100.0f, 50, 1.0f, true);
}
