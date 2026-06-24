#include "hooks.h"

#include <MinHook.h>

#include "../Global.h"

bool HK::Init()
{
    if (MH_STATUS status = MH_Initialize())
    {
        G::pOutput->Log(LOG_ERROR, "Hooks: Failed to initialize MinHook, status - %i", status);
        return false;
    }

    D3D::Init();

    return true;
}

void HK::Destroy()
{
    if (MH_STATUS status = MH_DisableHook(MH_ALL_HOOKS))
    {
        G::pOutput->Log(LOG_ERROR, "Hooks: Failed to disable hooks, status - %i", status);
    }

    MH_Uninitialize();
}
