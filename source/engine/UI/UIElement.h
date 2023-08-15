#pragma once

#include "../default_classes/Component.h"

class UIElement : public MovableComponent
{
public:
	UIElement(const glm::vec2& position, const glm::vec2& size);
	virtual ~UIElement();
};