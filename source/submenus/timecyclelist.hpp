#pragma once
#include <gtavmenubase/menu.h>
#include "../rage/TimecycleModifier.hpp"

namespace tce::subs::timecyclelist
{
	extern rage::TimecycleModifier* g_selected_modifier;

	void on_tick(NativeMenu::Menu &menu);
}
