#include "memorylocation.hpp"
#include <vector>

namespace tce::memory
{
	struct ModifiedMemoryData
	{
		MemoryLocation	loc;
		size_t			numModifiedBytes;
		uint8_t*        origBytes;
	};
	std::vector<ModifiedMemoryData> g_modifiedLocations;

	void MemoryLocation::saveBytes(const size_t numBytes)
	{
		ModifiedMemoryData data;

		data.loc = m_location;
		data.numModifiedBytes = numBytes;
		data.origBytes = new uint8_t[numBytes];

		memcpy(data.origBytes, m_location, numBytes);

		g_modifiedLocations.push_back(data);
	}

	void MemoryLocation::restore()
	{
		for (int i = static_cast<int>(g_modifiedLocations.size() - 1); i >= 0; i--)
		{
			ModifiedMemoryData* data = &g_modifiedLocations[i];
			if (m_location == data->loc.m_location)
			{
				// Can't use write_vp, because that would push the modified bytes in g_modifiedLocations
				uint32_t oldProtect;
				protect(data->numModifiedBytes, PAGE_EXECUTE_READWRITE, &oldProtect);
				memcpy(m_location, data->origBytes, data->numModifiedBytes);
				protect(data->numModifiedBytes, oldProtect, nullptr);

				delete[] data->origBytes;
				g_modifiedLocations.erase(g_modifiedLocations.begin() + i);
			}
		}
	}

	void RestoreAllModifiedBytes()
	{
		while (g_modifiedLocations.size())
		{
			g_modifiedLocations[0].loc.restore();
		}
	}
}
