#include "Source/Public/Request.h"
#include <Source/Public/Finders.h>
#include <Platinum.h>

bool Request::ProcessRequest(Containers::FCurlHttpRequest* HttpRequest)
{
    auto url = HttpRequest->GetURL().ToString();
    if (url && std::wcsstr(url, L"epicgames.com"))
    {
        HttpRequest->SetURL(Platinum::BackendURL);

        std::wcout << HttpRequest->GetURL().ToString() << std::endl;
    }

    return Originals::ProcessRequest(HttpRequest);
}

void Request::Patch()
{
    Hook(Finders::FindProcessRequest(), ProcessRequest, (void**)&Originals::ProcessRequest);
}