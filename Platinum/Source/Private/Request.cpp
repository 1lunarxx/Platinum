#include "Source/Public/Request.h"
#include <Source/Public/Finders.h>
#include <fstream>
#include <iostream>

bool Request::ProcessRequest(Containers::FCurlHttpRequest HttpRequest)
{
    HttpRequest.GetURL().ToString();

    return Originals::ProcessRequest(HttpRequest);
}

void Request::Patch()
{
    Hook(Finders::FindProcessRequest(), ProcessRequest, (void**)&Originals::ProcessRequest);
}