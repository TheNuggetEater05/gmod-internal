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

    while (!GetAsyncKeyState(QUIT_KEY))
        Sleep(10);

    G::ExitModule();
}