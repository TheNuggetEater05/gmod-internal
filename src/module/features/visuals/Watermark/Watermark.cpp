#include "Watermark.h"
#include "../../../renderer/Renderer.h"

#include "../../../types/Vector.h"
#include "../../../types/Color.h"

#include "../../../Settings.h"

void Watermark::Render()
{
	Renderer::Get().DrawText("GMOD INTERNAL v2", { 10, 10 }, g_Settings.Visuals.Watermark.color);
}
