#include "../stdafx.h"
#include "memory.hpp"
#include <Windows.h>
#include "patternscan.h"

namespace tce::memory
{
	uint64_t get_base()
	{
		static uint64_t base = reinterpret_cast<uint64_t>(GetModuleHandle(NULL));
		return base;
	}

	rage::TimecylceModifierPool* get_timecycle_pool()
	{
		static rage::TimecylceModifierPool* pool = "48 89 7B 10 8B 05 ? ? ? ?"_Scan.add(0x11).add(3).rip(4);

		return pool;
	}

	const char* get_timecycle_modifier_value_name(uint32_t type)
	{
		static const MemoryLocation names = "48 8D 3D ? ? ? ? 48 8D 99 ? ? ? ?"_Scan.get_lea();


		return *names.add(0x20 * type).as<const char**>();
	}
}
