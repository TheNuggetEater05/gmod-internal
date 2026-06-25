#include "Visuals.h"

#include "../../Settings.h"

#include "Watermark/Watermark.h"

void Visuals::Render()
{
	if (g_Settings.Visuals.Watermark.enabled)
		Watermark::Get().Render();
}