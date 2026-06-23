#pragma once

#ifndef RENDER_H
#define RENDER_H

#include "../../utility/Singleton.h"

class Render : public Singleton<Render>
{
	friend class Singleton<Render>;
public:
	bool Init();
	void Destroy();

	void* GetDevice();

private:
	bool _SetupWindow();
	void _DestroyWindow();

private:
	bool m_Initialized = false;
};

#endif