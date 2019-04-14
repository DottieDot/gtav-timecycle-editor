#pragma once
#include <cstdint>
#include "../rage/TimecycleModifierPool.hpp"

namespace tce::memory
{
	uint64_t get_base();

	rage::TimecylceModifierPool* get_timecycle_pool();
}