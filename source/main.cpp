#include "stdafx.h"

#include "main.hpp"

namespace tce
{
	NativeMenu::Menu g_menu = NativeMenu::Menu();;

	void script_main()
	{
		g_menu.SetFiles("Timecylce Editor/setting_menu.ini");
		g_menu.ReadSettings();

		for (;;)
		{
			

			WAIT(0);
		}
	}
}
