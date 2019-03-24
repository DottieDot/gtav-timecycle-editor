#pragma once
#include <cstdint>
#include <cstring>
#include <initializer_list>
#include <exception>

namespace rage
{
	template <typename T>
	class atArray
	{
	public:
		T* m_offset;
		uint16_t m_count;
		uint16_t m_size;
	};
}
