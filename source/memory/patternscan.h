#pragma once
#include <cstdint>
#include <Windows.h>
#include "memorylocation.hpp"

namespace tce::memory
{
	tce::memory::MemoryLocation PatternScan(const char* sig, const char* mask, HMODULE hModule = NULL);
}

tce::memory::MemoryLocation operator ""_Scan(const char* pattern, size_t len);
