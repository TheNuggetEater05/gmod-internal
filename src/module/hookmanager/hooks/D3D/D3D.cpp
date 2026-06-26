#include "D3D.h"

#include <Memory.h>
#include "../../../logger/Logger.h"

#include "../../../renderer/Renderer.h"
#include "../../../types/Vector.h"
#include "../../../types/Color.h"

namespace D3D
{
	EndSceneFn oEndScene = nullptr;
	ResetFn oReset = nullptr;

	IDirect3DDevice9* pDevice = nullptr;
	IDirect3DDevice9* pDeviceTemp = nullptr;
	D3DDEVICE_CREATION_PARAMETERS creationParams{};

	bool Init()
	{
		IDirect3D9* pD3D = Direct3DCreate9(D3D_SDK_VERSION);
		if (!pD3D)
		{
			Logger::Get().Log(LOG_ERROR, "D3D Hook: Failed to create D3D");
			return false;
		}

		D3DPRESENT_PARAMETERS params = {};
		params.Windowed = 1;
		params.SwapEffect = D3DSWAPEFFECT_DISCARD;
		params.hDeviceWindow = GetForegroundWindow();

		if (FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, params.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &params, &pDeviceTemp)))
		{
			Logger::Get().Log(LOG_ERROR, "D3D Hook: Failed to create temporary device");
			return false;
		}

		void** vtD3D = Memory::GetVTable(pDeviceTemp);

		Logger::Get().Log(LOG_SUCCESS, "D3D Hook: Created temporary device @ %p", pDeviceTemp);
		Logger::Get().Log(LOG_SUCCESS, "D3D Hook: Found EndScene virtual function @ %p", vtD3D[42]);
		Logger::Get().Log(LOG_SUCCESS, "D3D Hook: Found Reset virtual function @ %p", vtD3D[16]);

		pD3D->Release();

		return true;
	}

	void Cleanup()
	{
		pDeviceTemp->Release();
	}

	long __stdcall hkEndScene(IDirect3DDevice9* pDevice)
	{
		if (!D3D::pDevice)
		{
			D3D::pDevice = pDevice;
			pDevice->GetCreationParameters(&D3D::creationParams);

			//D3D::pDeviceTemp->Release();
			Logger::Get().Log(LOG_SUCCESS, "D3D Hook: Captured game's device @ %p", D3D::pDevice);
			Logger::Get().Log(LOG_SUCCESS, "D3D Hook: Captured device's creation parameters @ %p", D3D::creationParams);

			Renderer::Get().Init();
		}

		if (!Renderer::Get().IsInitialized())
			Renderer::Get().Init();

		if (Renderer::Get().IsDestroying())
			return oEndScene(pDevice);

		Renderer::Get().StartRender();

		Renderer::Get().EndRender();

		return oEndScene(pDevice);
	}

	HRESULT __stdcall hkReset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pParams)
	{
		HRESULT result = oReset(pDevice, pParams);

		return result;
	}
}