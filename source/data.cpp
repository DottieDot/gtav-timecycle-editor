#include "stdafx.h"
#include "data.hpp"
#include <fstream>

namespace tce::data
{
	std::unordered_map<uint32_t, std::string> g_timecycle_modifier_names = {};

	void load_timecycle_modifier_names()
	{
		auto file = std::ifstream("tce/names.txt");

		if (!file.is_open())
		{
			throw std::exception("Failed to open names.txt");
		}

		while (!file.eof())
		{
			std::string line;
			std::getline(file, line);

			if (!line.empty())
			{
				g_timecycle_modifier_names[GAMEPLAY::GET_HASH_KEY(ccast<char*>(line.c_str()))] = line;
			}
		}
	}
}
