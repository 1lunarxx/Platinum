#pragma once
#include "framework.h"

namespace Platinum
{
	static bool bLog = true;
	static bool bConsole = true;
	static const wchar_t* BackendURL = L"http://localhost:3551";

	double FNVer = ([]() {
		auto FNBuild = Memcury::Scanner::FindPattern("2b 00 2b 00 46 00 6f 00 72 00 74 00 6e 00 69 00 74 00 65 00 2b 00 52 00 65 00 6c 00 65 00 61 00 73 00 65 00 2d 00").Get();
		auto VStart = wcschr((wchar_t*)FNBuild, '-') + 1;
		auto VEnd = wcschr(VStart, '-');
		if (!VEnd) VEnd = (wchar_t*)FNBuild + wcslen((wchar_t*)FNBuild);
		auto sz = (VEnd - VStart) * 2;
		wchar_t* s = (wchar_t*)malloc(sz + 2);
		__movsb((PBYTE)s, (const PBYTE)VStart, sz);
		s[sz] = 0;
		wchar_t* e;
		return wcstod(s, &e);
	})();
}