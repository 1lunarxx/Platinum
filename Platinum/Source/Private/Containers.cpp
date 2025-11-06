#include "Source/Public/Containers.h"

Containers::FString::FString(const wchar_t* str)
{
    if (!str || !*str) {
        Data = nullptr;
        NumElements = MaxElements = 0;
        return;
    }

    NumElements = MaxElements = static_cast<int>(wcslen(str)) + 1;
    Data = static_cast<wchar_t*>(FMemory::Malloc(NumElements * sizeof(wchar_t)));
    memcpy_s(Data, NumElements * sizeof(wchar_t), str, NumElements * sizeof(wchar_t));
}

wchar_t* Containers::FString::ToString()
{
    return Data;
}

Containers::FString Containers::FCurlHttpRequest::GetURL()
{
    FString Result;
    auto fn = (FString & (*)(FCurlHttpRequest*, FString&))(*VTable);
    fn(this, Result);
    return Result;
}

void Containers::FCurlHttpRequest::SetURL(const wchar_t* url)
{
    FString str(url);
    auto fn = (void (*)(FCurlHttpRequest*, FString&))VTable[10];
    fn(this, str);
}