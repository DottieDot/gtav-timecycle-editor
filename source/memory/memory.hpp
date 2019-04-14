#pragma once
#include <cstdint>
#include "../rage/TimecycleModifierPool.hpp"

namespace tce::memory
{
	uint64_t get_base();

	rage::TimecylceModifierPool* get_timecycle_pool();

	const char* get_timecycle_modifier_value_name(uint32_t type);
}