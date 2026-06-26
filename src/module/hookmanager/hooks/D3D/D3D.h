#pragma once

#ifndef D3D_H
#define D3D_H

#include <d3d9.h>

namespace D3D
{
	using EndSceneFn = long(__stdcall*)(IDirect3DDevice9* pDevice);
	using ResetFn = HRESULT(__stdcall*)(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pParams);

	extern EndSceneFn oEndScene;
	extern ResetFn oReset;

	extern IDirect3DDevice9* pDevice;
	extern IDirect3DDevice9* pDeviceTemp;
	extern D3DDEVICE_CREATION_PARAMETERS creationParams;

	long __stdcall hkEndScene(IDirect3DDevice9* pDevice);
	HRESULT __stdcall hkReset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pParams);

	bool Init();
	//void Cleanup();
}

#endif // !D3D_H
