#include "Source/Public/Finders.h"

uintptr_t Finders::FindProcessRequest()
{
    const std::vector<uint8_t> p1 = { 0x48, 0x81, 0xEC };
    const std::vector<uint8_t> p2 = { 0x40 };
    const std::vector<uint8_t> p3 = { 0x48, 0x8B, 0xC4 };
    const std::vector<uint8_t> p4 = { 0x4C, 0x8B, 0xDC };
    const std::vector<uint8_t> p5 = { 0x48, 0x83, 0xEC };

    auto s = Memcury::Scanner::FindStringRef(L"STAT_FCurlHttpRequest_ProcessRequest", Memcury::PE::GetModuleBase(), false);
    if (!s.IsValid()) s = Memcury::Scanner::FindStringRef(L"STAT_FCurlHttpRequest_ProcessRequest");

    uintptr_t addr = 0;
    if (s.IsValid()) {
        addr = s.ScanFor(p1, false).ScanFor(p2, false).Get();
        if (!addr) addr = s.ScanFor(p5, false).ScanFor(p2, false).Get();
        if (!addr) addr = s.ScanFor(p3, false).Get();
        if (!addr) addr = s.ScanFor(p4, false).Get();
    }

    return addr;
}