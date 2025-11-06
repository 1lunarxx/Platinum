#include "Source/Public/Request.h"
#include <Source/Public/Finders.h>
#include <Platinum.h>

bool Request::ProcessRequest(Containers::FCurlHttpRequest* HttpRequest)
{
    auto url = HttpRequest->GetURL().ToString();
    static int RequestCount = 0;
    RequestCount++;

    // idk how else to do this
    if (RequestCount == 10)
    {
        auto EOSHandle = reinterpret_cast<uintptr_t>(GetModuleHandleA("EOSSDK-Win64-Shipping.dll"));
        if (EOSHandle)
        {
            printf("EOSHandle");
            auto Scanner = Memcury::Scanner::FindStringRef(L"ProcessRequest failed. URL '%s' is not using a whitelisted domain. %p", EOSHandle);

            Originals::EOSProcessRequest = Scanner.ScanFor({ 0x48, 0x89, 0x5C }, false).GetAs<decltype(Originals::EOSProcessRequest)>();
            auto Ref = Memcury::Scanner::FindPointerRef(reinterpret_cast<void*>(Originals::EOSProcessRequest), EOSHandle).GetAs<void**>();

            if (Ref)
            {
                DWORD oldProtect;
                if (VirtualProtect(Ref, sizeof(void*), PAGE_EXECUTE_READWRITE, &oldProtect))
                {
                    *Ref = reinterpret_cast<void*>(EOSProcessRequest);
                    VirtualProtect(Ref, sizeof(void*), oldProtect, &oldProtect);
                }
            }
        }
    }

    if (url && std::wcsstr(url, L"epicgames.com"))
    {
        std::wstring newurl = Platinum::BackendURL;

        const wchar_t* endpoint = std::wcsstr(url, L"epicgames.com");
        if (endpoint)
        {
            endpoint += wcslen(L"epicgames.com");
            if (*endpoint != L'/') newurl += L'/';
            newurl += endpoint;
        }

        HttpRequest->SetURL(newurl.c_str());
    }

    return Originals::ProcessRequest(HttpRequest);
}

bool Request::EOSProcessRequest(Containers::FCurlHttpRequest* HttpRequest)
{
    auto url = HttpRequest->GetURL().ToString();

    if (url && std::wcsstr(url, L"epicgames.dev"))
    {
        std::wstring newurl = Platinum::BackendURL;

        const wchar_t* endpoint = std::wcsstr(url, L"epicgames.dev");
        if (endpoint)
        {
            endpoint += wcslen(L"epicgames.com");
            if (*endpoint != L'/') newurl += L'/';
            newurl += endpoint;
        }

        HttpRequest->SetURL(newurl.c_str());
    }

    return Originals::EOSProcessRequest(HttpRequest);
}

// cant minhook..
void Request::Patch()
{
    uintptr_t ProcessRequestAddr = Finders::FindProcessRequest();
    if (!ProcessRequestAddr) return;

    Originals::ProcessRequest = reinterpret_cast<decltype(Originals::ProcessRequest)>(ProcessRequestAddr);

    void** PointerRef = Memcury::Scanner::FindPointerRef((void*)ProcessRequestAddr).GetAs<void**>();
    if (PointerRef)
    {
        DWORD oldProtect;
        if (VirtualProtect(PointerRef, sizeof(void*), PAGE_EXECUTE_READWRITE, &oldProtect))
        {
            *PointerRef = reinterpret_cast<void*>(ProcessRequest);
            VirtualProtect(PointerRef, sizeof(void*), oldProtect, &oldProtect);
        }
    }

    //Hook(Finders::FindProcessRequest(), ProcessRequest, (void**)&Originals::ProcessRequest);
}