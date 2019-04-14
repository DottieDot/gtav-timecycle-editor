#include "../stdafx.h"
#include "timecycle.hpp"
#include "timecyclelist.hpp"
#include "../data.hpp"

rage::TimecycleModifierValue* tce::subs::timecycle::g_selected_modifier_value = nullptr;

void tce::subs::timecycle::on_tick(NativeMenu::Menu& menu)
{
	auto* modifier = tce::subs::timecyclelist::g_selected_modifier;

	menu.Title(data::g_timecycle_modifier_names[modifier->m_nameHash]);

	if (menu.Option("Set Active"))
	{

	}

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
