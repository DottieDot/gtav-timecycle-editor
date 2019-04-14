#include "stdafx.h"
#include "submenus/include.hpp"
#include "main.hpp"
#include "data.hpp"

namespace tce
{
	NativeMenu::Menu g_menu = NativeMenu::Menu();

	void script_main()
	{
		g_menu.SetFiles("tce/setting.ini");
		g_menu.ReadSettings();
		g_menu.cheatString = "timecycles";

		data::load_timecycle_modifier_names();

		g_menu.OpenMenu();
		for (;;)
		{
			g_menu.CheckKeys();

			if (g_menu.CurrentMenu("mainmenu"))
			{
				subs::timecyclelist::on_tick(g_menu);
			}
			else if (g_menu.CurrentMenu("timecycle"))
			{
				subs::timecycle::on_tick(g_menu);
			}
			else if (g_menu.CurrentMenu("timecyclemodifier_value"))
			{
				subs::timecyclemodifier_value::on_tick(g_menu);
			}

			WAIT(0);
		}
	}
}
