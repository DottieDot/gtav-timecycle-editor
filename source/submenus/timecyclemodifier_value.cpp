#include "timecyclemodifier_value.hpp"
#include "../stdafx.h"
#include "timecycle.hpp"

void tce::subs::timecyclemodifier_value::on_tick(NativeMenu::Menu& menu)
{
	auto* value = timecycle::g_selected_modifier_value;

	menu.Title(memory::get_timecycle_modifier_value_name(value->m_type));

	menu.FloatOption("Light", value->m_lightValue, -1000.f, 1000.f, 0.1f);
	menu.FloatOption("Dark", value->m_darkValue, -1000.f, 1000.f, 0.1f);

	menu.EndMenu();

}
