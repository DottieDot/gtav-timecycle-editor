#pragma once
#include <gtavmenubase/menu.h>
#include "../rage/TimecycleModifier.hpp"

namespace tce::subs::timecycle
{
	extern rage::TimecycleModifierValue* g_selected_modifier_value;

	void on_tick(NativeMenu::Menu& menu);
}
