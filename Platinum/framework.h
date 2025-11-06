#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <thread>
#include <string>
#include <iostream>
#include "Libraries/Memcury.h"
#include "Libraries/Minhook.h"

inline void Hook(uintptr_t Offset, void* Detour, void** OG = nullptr)
{
	MH_CreateHook((LPVOID)Offset, Detour, OG);
	MH_EnableHook((LPVOID)Offset);
}