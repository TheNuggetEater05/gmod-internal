#include "Render.h"

bool Render::Init()
{

	m_Initialized = true;
	return true;
}

void Render::Destroy()
{
}

void* Render::GetDevice()
{
	if (!m_Initialized)
		Init();
}