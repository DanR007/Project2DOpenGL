#pragma once

#include <vector>

class Widget;

class HUDManager
{
public:
	HUDManager();
	~HUDManager();

	Widget* CreateWidget();

	Widget* GetWidget(const size_t& id) { return _all_widgets[id]; };

	void Erase(Widget* widget);

	void Clear();
private:
	std::vector<Widget*> _all_widgets;
};