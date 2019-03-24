#include "../stdafx.h"
#include "memory.hpp"
#include <Windows.h>

namespace tce::memory
{
	uint64_t get_base()
	{
		static uint64_t base = reinterpret_cast<uint64_t>(GetModuleHandle(NULL));
		return base;
	}
}
