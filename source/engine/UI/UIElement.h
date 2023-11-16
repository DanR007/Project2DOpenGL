#pragma once

#include "../default_classes/Component.h"

class UIElement : public MovableComponent
{
public:
	UIElement(const glm::vec2& position, const glm::vec2& size);
	virtual ~UIElement();

	/// @brief Используется чтобы поменять не только свою позицию, но и зависимого элемента(-ов)
    /// @param position 
    virtual void ChangePosition(const glm::vec2& position);
};