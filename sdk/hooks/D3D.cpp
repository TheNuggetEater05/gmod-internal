#include "D3D.h"

#include <intrin.h>

#include <MinHook.h>
#include <imgui_impl_dx9.h>

#include "../../Global.h"

D3DCOLOR RainbowColor(float speed = 1.0f)
{
	float t = GetTickCount64() * 0.001f * speed;

	float r = sinf(t) * 0.5f + 0.5f;
	float g = sinf(t + 2.094f) * 0.5f + 0.5f; // +120°
	float b = sinf(t + 4.188f) * 0.5f + 0.5f; // +240°

	return D3DCOLOR_ARGB(
		255,
		static_cast<int>(r * 255.f),
		static_cast<int>(g * 255.f),
		static_cast<int>(b * 255.f)
	);
}

static long __stdcall HK::D3D::FN::hEndScene(IDirect3DDevice9* pDevice)
{
	if (!D3D::pDevice)
	{
		D3D::pDevice = pDevice;
		G::pOutput->Log(LOG_SUCCESS, "D3D: Captured game's device @ %p", D3D::pDevice);
	}

	if (!G::pRender->IsInit())
	{
		G::pRender->Init(pDevice);
	}

	if (G::pRender->IsDestroying())
	{
		return oEndScene(pDevice);
	}
	
	if (G::pRender->IsMenuOpen())
	{
		G::pRender->DrawMenu();
	}

	G::pRender->DrawString(Vec2::Zero(), RainbowColor(), "gmod-internal", true, false);

	return oEndScene(pDevice);
}

static HRESULT __stdcall HK::D3D::FN::hReset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pParams)
{
	HRESULT result = oReset(pDevice, pParams);

	return result;
}

bool HK::D3D::Init()
{
	IDirect3D9* pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (pD3D == nullptr)
	{
		G::pOutput->Log(LOG_ERROR, "D3D: Failed to create D3D9");
		return false;
	}

	D3DPRESENT_PARAMETERS d3DParams = {};
	d3DParams.Windowed = 1;
	d3DParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3DParams.hDeviceWindow = GetForegroundWindow();

	IDirect3DDevice9* pDeviceTemp = nullptr;

	if (FAILED(pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3DParams.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3DParams, &pDeviceTemp)))
	{
		G::pOutput->Log(LOG_ERROR, "D3D: Failed to create temporary device");
		return false;
	}

	if (!pDeviceTemp)
	{
		pD3D->Release();
		return false;
	}

	void** vtD3D = Memory::GetVTable(pDeviceTemp);

	G::pOutput->Log(LOG_SUCCESS, "D3D: Created temporary device @ %p", pDeviceTemp);
	G::pOutput->Log(LOG_SUCCESS, "D3D: Found EndScene @ %p", vtD3D[42]);
	G::pOutput->Log(LOG_SUCCESS, "D3D: Found Reset @ %p", vtD3D[16]);
	G::pOutput->Log("D3D: Setting hooks");

	if (MH_STATUS status = MH_CreateHook(vtD3D[42], &FN::hEndScene, reinterpret_cast<void**>(&FN::oEndScene)))
	{
		G::pOutput->Log(LOG_ERROR, "D3D: Failed to create endscene hook, status - %i", status);
	}
	if (MH_STATUS status = MH_CreateHook(vtD3D[16], &FN::hReset, reinterpret_cast<void**>(&FN::oReset)))
	{
		G::pOutput->Log(LOG_ERROR, "D3D: Failed to create reset hook, status - %i", status);
	}

	MH_EnableHook(vtD3D[42]);
	MH_EnableHook(vtD3D[16]);

	G::pOutput->Log(LOG_SUCCESS, "D3D: Set hooks");

	pDeviceTemp->Release();
	pD3D->Release();
}
