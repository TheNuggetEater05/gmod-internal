#pragma once

#ifndef HOOKS_H
#define HOOKS_H

#include <d3d9.h>

namespace HK
{
	void Init();
	void Destroy();

	namespace DX
	{
		using EndSceneFn = long(__thiscall*)(void*, IDirect3DDevice9*);
		inline EndSceneFn oEndScene = nullptr;

		long __stdcall hEndScene(IDirect3DDevice9* pDevice);

		using ResetFn = HRESULT(__thiscall*)(void*, IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);
		inline ResetFn oReset = nullptr;

		HRESULT __stdcall hReset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pParams);
	}
}

#endif