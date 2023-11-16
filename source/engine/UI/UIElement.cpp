#include "UIElement.h"

UIElement::UIElement(const glm::vec2& position, const glm::vec2& size):
	MovableComponent(nullptr, position, size)
{
}

UIElement::~UIElement()
{
}

void UIElement::ChangePosition(const glm::vec2 &position)
{
	SetPosition(position);
}
