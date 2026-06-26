#include "Visuals.h"

#include "../../Settings.h"

#include "Watermark/Watermark.h"
#include "ESP/ESP.h"

void Visuals::Init()
{
	ESP::Get().Init();
}

void Visuals::Render()
{
	if (g_Settings.Visuals.Watermark.enabled)
		Watermark::Get().Render();

	if (g_Settings.Visuals.ESP.enabled)
		ESP::Get().Render();
}