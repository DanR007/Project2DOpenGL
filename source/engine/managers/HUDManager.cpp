#include "HUDManager.h"

#include "../UI/Widget.h"

#ifdef __linux__
#include <algorithm>
#endif //__linux__


HUDManager::HUDManager()
{
}

HUDManager::~HUDManager()
{
	Clear();
}

Widget* HUDManager::CreateWidget()
{
	Widget* wdg = new Widget();
	_all_widgets.emplace_back(wdg);
	return wdg;
}

void HUDManager::Erase(Widget* widget)
{
	auto it = std::find(_all_widgets.begin(), _all_widgets.end(), widget);
	_all_widgets.erase(it);
}

void HUDManager::Clear()
{
	for (Widget* w : _all_widgets)
	{
		if (w)
		{
			w->Destroy();
			w = nullptr;
		}
	}
	_all_widgets.clear();
}
