#include "Widget.h"

Widget::Widget():Component()
{
}

Widget::~Widget()
{
	for (UIElement* element : _ui_elements)
	{
		element->Destroy();
	}
}
