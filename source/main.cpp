#include "stdafx.h"
#include "submenus/include.hpp"

#include "main.hpp"

namespace tce
{
	NativeMenu::Menu g_menu = NativeMenu::Menu();;

	void script_main()
	{
		g_menu.SetFiles("tce/setting.ini");
		g_menu.ReadSettings();

		g_menu.cheatString = "timecycles";
		g_menu.OpenMenu();
		for (;;)
		{
			if (g_menu.CurrentMenu("mainmenu"))
			{
				subs::timecyclelist::on_tick(g_menu);
			}

			WAIT(0);
		}
	}
}
