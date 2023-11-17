#include "UIElement.h"

UIElement::UIElement(const glm::vec2& position, const glm::vec2& size):
	Component(nullptr, position, size)
{
}

UIElement::~UIElement()
{
}
