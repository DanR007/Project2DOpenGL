#pragma once

#include "../default_classes/Component.h"

#include "UIElement.h"

#include <vector>
#include <string>

class Widget : public Component
{
public:
	Widget();
	virtual ~Widget();

	template<typename T>
	T* AddElement(const glm::vec2& position, const glm::vec2& size)
	{
		T* element = new T(position, size);
		if (dynamic_cast<UIElement*>(element))
		{
			_ui_elements.push_back(element);
			return element;
		}

		return nullptr;
	}

	UIElement* operator[](int index)
	{
		return _ui_elements[index];
	}

private:
	std::vector<UIElement*> _ui_elements;
};