#include "timecyclelist.hpp"
#include "../stdafx.h"

rage::TimecycleModifier* tce::subs::timecyclelist::g_selectedModifier = nullptr;

void tce::subs::timecyclelist::on_tick(NativeMenu::Menu &menu)
{
	auto pool = memory::get_timecycle_pool();

	menu.Title("Timecycles");

	for (uint16_t i = 0; i < pool->m_modifiers.m_count; ++i)
	{
		auto* modifier = pool->m_modifiers.m_offset[i];

		char buf[0xFF];
		sprintf_s(buf, "0x%08X", modifier->m_nameHash);
		if (menu.MenuOption(buf, "timecycle"))
		{
			g_selectedModifier = modifier;
		}
	}

	menu.EndMenu();
}
