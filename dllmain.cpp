#include "Global.h"

#define QUIT_KEY VK_END

void Main(HMODULE hModule);

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        CloseHandle(CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Main), hModule, 0, 0));
        break;
    }
    return TRUE;
}

void Main(HMODULE hModule)
{
    G::InitializeModule(hModule);

    for (ClientClass* pClientClass = I::Client->GetAllClasses(); pClientClass; pClientClass = pClientClass->m_pNext)
    {
        G::pOutput->Log("[%s]", pClientClass->m_pNetworkName);
        //NVManager::Dump(pClientClass->m_pRecvTable);
    }

    

    while (!GetAsyncKeyState(QUIT_KEY))
    {
        for (int i = 1; i < 64; i++)
        {
            auto entity = static_cast<std::uint8_t*>(I::EntityList->GetClientEntity(i));

            if (!entity)
                continue;

            auto health = *reinterpret_cast<int*>(entity + 0xD8);

            if (!health)
                continue;

            auto velocityX = *reinterpret_cast<float*>(entity + 0x150);
            auto velocityY = *reinterpret_cast<float*>(entity + 0x154);
            auto velocityZ = *reinterpret_cast<float*>(entity + 0x158);

            auto jumpPower = *reinterpret_cast<const char**>(entity + 0x38AC);

            G::pOutput->Log("%i @ %p:", i, entity);
            G::pOutput->Log("Health %i", health);
            G::pOutput->Log("Velocity X %f", velocityX);
            G::pOutput->Log("Velocity Y %f", velocityY);
            G::pOutput->Log("Velocity Z %f", velocityZ);
            G::pOutput->Log("JumpPower %f", jumpPower);

        }
        Sleep(10);
    }

    G::ExitModule();
}