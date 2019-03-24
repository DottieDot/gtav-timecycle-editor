#include "../stdafx.h"
#include "patternscan.h"
#include "memory.hpp"
#include <psapi.h>

DWORD GetImageSize(HMODULE hModule)
{
	_MODULEINFO minfo;
	return GetModuleInformation(GetCurrentProcess(), hModule, &minfo, sizeof(minfo)) ? minfo.SizeOfImage : NULL;
}

tce::memory::MemoryLocation tce::memory::PatternScan(const char* sig, const char* mask, HMODULE hModule)
{
	HMODULE  base = hModule ? hModule : reinterpret_cast<HMODULE>(get_base());
	char* ptr = reinterpret_cast<char*>(base);
	char* end = reinterpret_cast<char*>(base + GetImageSize(base) - 0x100);
	size_t   ptrnLen = strlen(mask);
	size_t   byte = 0;

	__try
	{
		// Loop until the pointer had reached the end of the executble, or we reached the end of the pattern
		while (ptr < end && byte != ptrnLen)
		{
			// Check if the byte we're looking for matches or if we're on a unknown byte
			if (*ptr == sig[byte] || mask[byte] == '?')
			{
				++byte;
				++ptr;
			}
			else
			{
				ptr += byte == 0;

				byte = 0;
			}
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		return 0;
	}

	// Returns address of match or nullptr
	return reinterpret_cast<uint64_t>(ptr - ptrnLen) * (byte == ptrnLen);
}

char ByteStrToChar(const char chars[2])
{
	uint8_t vals[2];

	for (int i = 0; i < 2; ++i)
	{
		vals[i] = chars[i] - '0' - (0x7 * (chars[i] > '9'));
	}

	return (vals[0] * 0x10) + vals[1];
}

tce::memory::MemoryLocation operator""_Scan(const char* pattern, size_t len)
{
	char sig[0xFF];
	char mask[0xFF];

	// Get pattern length
	size_t ptrnLen = len;

	// Loop through pattern
	size_t j = 0;
	for (size_t i = 0; i < ptrnLen;)
	{
		// Skip over white spaces
		if (pattern[i] == ' ') continue;

		// yesyCheck if the byte isn't unknown
		if (pattern[i] != '?' && pattern[i] != '\0')
		{
			mask[j] = 'x';
			sig[j] = ByteStrToChar(pattern + i);

			i += 3;
		}
		else
		{
			mask[j] = '?';
			sig[j] = '\x00';

			i += 2;
		}
		++j;
	}

	mask[j] = '\0';

	return tce::memory::PatternScan(sig, mask);
}
