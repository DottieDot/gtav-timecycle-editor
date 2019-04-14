#include "timecycle.hpp"
#include "../stdafx.h"
#include "timecyclelist.hpp"

rage::TimecycleModifierValue* tce::subs::timecycle::g_selected_modifier_value = nullptr;

void tce::subs::timecycle::on_tick(NativeMenu::Menu& menu)
{
	auto* modifier = tce::subs::timecyclelist::g_selected_modifier;

	char buf[0xFF];
	sprintf_s(buf, "0x%08X", modifier->m_nameHash);

	menu.Title(buf);

	for (uint16_t i = 0; i < modifier->modifiers.m_count; ++i)
	{
		auto* value = &modifier->modifiers.m_offset[i];
		auto name = memory::get_timecycle_modifier_value_name(value->m_type);

		if (menu.MenuOption(name, "timecyclemodifier_value"))
		{
			g_selected_modifier_value = value;
		}
	}

	menu.EndMenu();
}
