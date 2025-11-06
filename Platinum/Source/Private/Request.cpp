#include "Source/Public/Request.h"
#include <Source/Public/Finders.h>

bool Request::ProcessRequest(Containers::FCurlHttpRequest HttpRequest)
{
    printf("ProcessRequest\n");

    auto URL = HttpRequest.GetURL();
    std::wcout << URL.ToString() << std::endl;

    return Originals::ProcessRequestOG(HttpRequest);
}

void Request::Patch()
{
    uintptr_t addr = Finders::FindProcessRequest();
    Originals::ProcessRequestOG = reinterpret_cast<decltype(Originals::ProcessRequestOG)>(addr);

    DWORD oldProtect;
    if (VirtualProtect(reinterpret_cast<void**>(addr), sizeof(void*), PAGE_EXECUTE_READWRITE, &oldProtect))
    {
        *reinterpret_cast<void**>(addr) = reinterpret_cast<void*>(&Request::ProcessRequest);
        VirtualProtect(reinterpret_cast<void**>(addr), sizeof(void*), oldProtect, &oldProtect);
    }
}