#include "Watermark.h"
#include "../../../renderer/Renderer.h"

#include "../../../types/Vector.h"
#include "../../../types/Color.h"

#include "../../../Settings.h"

void Watermark::Render()
{
	Renderer::Get().DrawText("spork alpha", {5, 5}, g_Settings.Visuals.Watermark.color, true, (float)g_Settings.Visuals.Watermark.size, Renderer::Get().GetFont("ProggyForever"));
}
