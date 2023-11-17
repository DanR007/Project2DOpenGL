#pragma once

#include <glm/vec2.hpp>

#include "Object.h"


class Component : public Object
{
public:
	Component(Object* owner = nullptr,
		const glm::vec2& position = glm::vec2(0.f),
		const glm::vec2& size = glm::vec2(1.f),
		const float& rotation = 0.f) : Object(position, size, rotation)
	{
		if(owner)
		{
			AttachTo(owner);
		}
	}
	virtual ~Component();
};