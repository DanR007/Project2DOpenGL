#include "Widget.h"

#include "UIElement.h"

Widget::Widget()
{
}

Widget::~Widget()
{
	for (UIElement* element : _ui_elements)
	{
		element->Destroy();
	}
}
