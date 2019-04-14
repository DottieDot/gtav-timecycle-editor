#include "timecycle.hpp"
#include "../stdafx.h"
#include "timecyclelist.hpp"

void tce::subs::timecycle::on_tick(NativeMenu::Menu& menu)
{
	auto* modifier = tce::subs::timecyclelist::g_selectedModifier;

	char buf[0xFF];
	sprintf_s(buf, "0x%08X", modifier->m_nameHash);

	menu.Title(buf);

	for (uint16_t i = 0; i < modifier->modifiers.m_count; ++i)
	{
		const auto* value = &modifier->modifiers.m_offset[i];
		auto name = memory::get_timecycle_modifier_value_name(value->m_type);

		menu.MenuOption(name, "timecyclemodifier_value");
	}

	menu.EndMenu();
}
