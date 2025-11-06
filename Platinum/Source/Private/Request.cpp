#include "Source/Public/Request.h"
#include <Source/Public/Finders.h>
#include <Platinum.h>

bool Request::ProcessRequest(Containers::FCurlHttpRequest* HttpRequest)
{
    auto url = HttpRequest->GetURL().ToString();

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

void Request::Patch()
{
    Hook(Finders::FindProcessRequest(), ProcessRequest, (void**)&Originals::ProcessRequest);
}