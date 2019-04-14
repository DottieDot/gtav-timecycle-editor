#pragma once
#include "TimecycleModifier.hpp"
#include "../util.hpp"

#pragma pack(push, 1)
namespace rage
{
	class TimecylceModifierPool
	{
	private:
		static inline bool nativeAlloc = false;

	public:
		atArray<TimecycleModifier*> m_modifiers;

		/*
		TimecycleModifier* getModifierByHash(uint32_t nameHash)
		{
			for (auto i = 0; i < m_modifiers.m_count; ++i)
			{
				if (m_modifiers.m_offset[i].m_nameHash == nameHash)
				{
					return &m_modifiers.m_offset[i];
				}
			}

			return nullptr;
		}

		void addModifier(TimecycleModifier modifier)
		{
			if (m_modifiers.m_count >= m_modifiers.m_size)
			{
				auto tmp = m_modifiers.m_offset;
				m_modifiers.m_offset = new TimecycleModifier[scast<size_t>(m_modifiers.m_size += 10)];
				std::memcpy(m_modifiers.m_offset, tmp, m_modifiers.m_count);

				if (nativeAlloc)
				{
					delete[] tmp;
				}
				else nativeAlloc = true;
			}

			m_modifiers.m_offset[m_modifiers.m_count++] = modifier;
		}*/
	};
}
#pragma pack(pop)
