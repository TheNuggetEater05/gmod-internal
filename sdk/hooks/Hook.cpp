#include "Hook.h"

#include <intrin.h>

#include <MinHook.h>

#include "../../Global.h"

void HK::Init()
{
	if (MH_Initialize())
		G::ExitModule("Hooks: Failed to intialize MinHook");

	if (MH_CreateHook(Memory::GetVFunc<DX::EndSceneFn>(G::pRender->GetDevice(), 42), &DX::hEndScene, reinterpret_cast<void**>(&DX::oEndScene)))
		G::ExitModule("Hooks: Failed to hook DX::EndScene");

	if (MH_CreateHook(Memory::GetVFunc<DX::ResetFn>(G::pRender->GetDevice(), 16), &DX::hReset, reinterpret_cast<void**>(&DX::oReset)))
		G::ExitModule("Hooks: Failed to hook DX::Reset");

	if (MH_EnableHook(MH_ALL_HOOKS))
		G::ExitModule("Hooks: Failed to enabled hooks");
}

void HK::Destroy()
{
	MH_DisableHook(MH_ALL_HOOKS);
	MH_RemoveHook(MH_ALL_HOOKS);
	MH_Uninitialize();
}

long HK::DX::hEndScene(IDirect3DDevice9* pDevice)
{
	const long result = oEndScene(pDevice, pDevice);

	G::pOutput->Log("EndScene called");

	return result;
}

HRESULT __stdcall HK::DX::hReset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pParams)
{
	const HRESULT result = oReset(pDevice, pDevice, pParams);

	G::pOutput->Log("Reset called");

	return result;
}