#pragma once
#include <cstdint>
#include <vector>
#include <Windows.h>

namespace tce::memory
{
	class MemoryLocation
	{
	private:
		void* m_location;

		void saveBytes(const size_t numBytes);

	public:
		MemoryLocation()
			: m_location(nullptr) { }

		template <typename T>
		MemoryLocation(T address)
			: m_location(*(void**)(&address)) { }

		MemoryLocation(const MemoryLocation& cpy)
			: m_location(cpy.m_location) { }

		template <typename T>
		T as() const
		{
			return reinterpret_cast<T>(m_location);
		}

		template <>
		void* as() const
		{
			return m_location;
		}

		template <typename T>
		operator T() const
		{
			return as<T>();
		}

		bool operator==(const MemoryLocation& loc) const
		{
			return m_location == loc.m_location;
		}

		bool operator!=(const MemoryLocation& loc) const
		{
			return m_location != loc.m_location;
		}

		bool operator>(const MemoryLocation& loc) const
		{
			return m_location > loc.m_location;
		}

		bool operator<(const MemoryLocation& loc) const
		{
			return m_location < loc.m_location;
		}

		bool operator>=(const MemoryLocation& loc) const
		{
			return m_location >= loc.m_location;
		}

		bool operator<=(const MemoryLocation& loc) const
		{
			return m_location <= loc.m_location;
		}

		template <typename T>
		MemoryLocation add(const T offset) const
		{
			return as<uint64_t>() + offset;
		}

		template <typename T>
		MemoryLocation sub(const T offset) const
		{
			return as<uint64_t>() - offset;
		}

		template <typename T>
		MemoryLocation rip(const T offset) const
		{
			return add(offset).add(*as<int*>());
		}

		bool protect(const size_t size, const uint32_t newProtect, const uint32_t* oldProtect) const
		{
			return VirtualProtect(as<void*>(), size, (DWORD)newProtect, (DWORD*)& oldProtect) == TRUE;
		}

		void set(const uint8_t value, const size_t bytes)
		{
			saveBytes(bytes);
			memset(m_location, value, bytes);
		}

		bool set_vp(const uint8_t value, const size_t bytes)
		{
			uint32_t oldProtect;

			if (protect(bytes, PAGE_EXECUTE_READWRITE, &oldProtect))
			{
				set(value, bytes);
				protect(bytes, oldProtect, nullptr);

				return true;
			}

			return false;
		}

		template <typename T>
		void write(const T value)
		{
			static_assert(std::is_trivially_copyable<T>::value, "Type is not trivially copyable");

			saveBytes(sizeof(T));
			*as<T*>() = value;
		}

		template <typename T>
		bool write_vp(const T value)
		{
			uint32_t oldProtect;

			size_t size = sizeof(value);

			if (protect(size, PAGE_EXECUTE_READWRITE, &oldProtect))
			{
				write(value);
				protect(size, oldProtect, nullptr);

				return true;
			}

			return false;
		}

		bool nop(const size_t bytes)
		{
			return set_vp(0x90, bytes);
		}

		bool ret(uint16_t stackSize = 0)
		{
			if (stackSize)
			{
				return write_vp<BYTE>(0xC2) &&
					add(1).write_vp(stackSize);
			}
			else
			{
				return write_vp<BYTE>(0xC3);
			}
		}

		bool call(const MemoryLocation& location)
		{
			return write_vp<BYTE>(0xE8) &&
				add(1).write_vp<uint32_t>(location.sub(as<uint64_t>() - 5));
		}

		void write_array(const std::vector<uint8_t>& bytes)
		{
			saveBytes(bytes.size());
			memcpy(as<void*>(), bytes.data(), bytes.size());
		}

		bool write_vp_array(const std::vector<uint8_t>& bytes)
		{
			uint32_t oldProtect;
			if (protect(bytes.size(), PAGE_EXECUTE_READWRITE, &oldProtect))
			{
				write_array(bytes);
				protect(bytes.size(), oldProtect, nullptr);

				return true;
			}
			
			return false;
		}

		template <typename T>
		T read()
		{
			return *reinterpret_cast<T*>(m_location);
		}

		MemoryLocation get_call() const
		{
			return add(1).rip(4);
		}

		bool jmp(const MemoryLocation & location)
		{
			return write_vp<BYTE>(0xE9) &&
				add(1).write_vp<uint32_t>(location.sub(as<uint64_t>() - 5));
		}

		MemoryLocation get_jmp() const
		{
			return get_call();
		}

		MemoryLocation get_lea() const
		{
			return add(3).rip(4);
		}

		template <typename T>
		void set_value(T val)
		{
			*as<T*> = val;
		}

		void restore();

	};

	void RestoreAllModifiedBytes();
}
