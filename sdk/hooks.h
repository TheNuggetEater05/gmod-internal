#pragma once

#ifndef HOOKS_H
#define HOOKS_H

#include "hooks/D3D.h"

namespace HK
{
	bool Init();
	void Destroy();

	namespace D3D
	{
		extern IDirect3DDevice9* pDevice;
	}
}

#endif