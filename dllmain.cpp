#include "Global.h"

void Main(HMODULE hModule);

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Main), hModule, 0, 0);
        break;
    }
    return TRUE;
}

void Main(HMODULE hModule)
{
    glb::hMod = hModule;

    glb::Init();

    glb::Output->Log("Entity list: 0x%p", glb::iface::pClientEntityList);
    glb::Output->Log("# of entities %i", glb::iface::pClientEntityList->NumberOfEntities(false));

    for (int i = 1; i <= 64; i++)
    {
        IClientEntity* entity = glb::iface::pClientEntityList->GetClientEntity(i);

        if (!entity)
            continue;

        glb::Output->Log("Entity: 0x%p", entity);
    }

    while (!GetAsyncKeyState(VK_END))
        Sleep(10);

    glb::Exit();
}