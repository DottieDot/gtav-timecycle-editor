#pragma once
#include <unordered_map>
#include <string>

namespace tce::data
{
	extern std::unordered_map<uint32_t, std::string> g_timecycle_modifier_names;

	void load_timecycle_modifier_names();
}
