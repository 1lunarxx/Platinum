#include "framework.h"
#include "Platinum.h"
#include <Source/Public/Request.h>

void Main()
{
    if (Platinum::bConsole)
    {
        AllocConsole();
        FILE* F;
        freopen_s(&F, "CONOUT$", "w", stdout);
        SetConsoleTitleA("Platinum | https://github.com/1lunarxx/Platinum");
    }

    Request::Patch();
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

