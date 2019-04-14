#include "../stdafx.h"
#include "timecyclelist.hpp"
#include "../data.hpp"

rage::TimecycleModifier* tce::subs::timecyclelist::g_selected_modifier = nullptr;

void tce::subs::timecyclelist::on_tick(NativeMenu::Menu &menu)
{
	auto pool = memory::get_timecycle_pool();

	menu.Title("Timecycles");

	for (uint16_t i = 0; i < pool->m_modifiers.m_count; ++i)
	{
		auto* modifier = pool->m_modifiers.m_offset[i]; 

		if (menu.MenuOption(data::g_timecycle_modifier_names[modifier->m_nameHash], "timecycle"))
		{
			g_selected_modifier = modifier;
		}
	}

	menu.EndMenu();
}
