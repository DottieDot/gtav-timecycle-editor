#pragma once
#include <gtavmenubase/menu.h>
#include "../rage/TimecycleModifier.hpp"

namespace tce::subs::timecyclelist
{
	extern rage::TimecycleModifier* g_selectedModifier;

	void on_tick(NativeMenu::Menu &menu);
}
