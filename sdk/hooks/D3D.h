#pragma once

#ifndef D3D_H
#define D3D_H

#include <d3d9.h>

namespace HK::D3D
{
	bool Init();
	//void Destroy();

	inline IDirect3DDevice9* pDevice = nullptr;

	namespace FN
	{
		using EndSceneFn = HRESULT(__stdcall*)(IDirect3DDevice9*);
		inline EndSceneFn oEndScene = nullptr;

		static long __stdcall hEndScene(IDirect3DDevice9* pDevice);

		using ResetFn = HRESULT(__stdcall*)(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);
		inline ResetFn oReset = nullptr;

		static HRESULT __stdcall hReset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pParams);
	}
}

#endif