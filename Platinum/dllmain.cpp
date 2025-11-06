#include "framework.h"
#include "Platinum.h"
#include <Source/Public/Request.h>
#include <Source/Public/Client.h>

void Main()
{
    if (Platinum::bLog)
    {
        AllocConsole();
        FILE* F;
        freopen_s(&F, "CONOUT$", "w", stdout);
        SetConsoleTitleA("Platinum | https://github.com/1lunarxx/Platinum");
    }

    //MH_Initialize();
    Request::Patch();
    //Client::InitConsole();
    //MH_EnableHook(MH_ALL_HOOKS);
}

BOOL APIENTRY DllMain(HMODULE Module, DWORD Reason, LPVOID Reserved)
{
    switch (Reason)
    {
    case 1:
        std::thread(Main).detach();
        break;
    case 0:
        break;
    }
    return 1;
}

