#pragma once
#include "atArray.hpp"

#pragma pack(push, 1)
namespace rage
{
	class TimecycleModifierValue
	{
	public:
		uint32_t m_type; //0x0000
		float m_lightValue; //0x0004
		float m_darkValue; //0x0008
	};

	class TimecycleModifier
	{
	public:
		atArray<TimecycleModifierValue> modifiers; // 0x0000
		char pad_000C[4]; // 0x000C
		uint32_t m_nameHash; // 0x0010
		char pad_0014[12]; // 0x0014
		uint32_t m_userFlags; // 0x0020
	};
	
}
#pragma pack(pop)
