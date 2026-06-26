#include <Includes.h>
#include "module/Module.h"

#define QUIT_KEY VK_END

void Main(HMODULE hModule);

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        auto thread = CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Main), hModule, 0, 0);

        if (thread)
            CloseHandle(thread);

        break;
    }
    return TRUE;
}

void Main(HMODULE hModule)
{
    Module* pModule = &Module::Get();

    pModule->Start(hModule);

    while (!GetAsyncKeyState(QUIT_KEY))
    {
        pModule->Update();
    }

    pModule->Kill();
}