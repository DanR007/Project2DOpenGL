#pragma once
#include "../../engine/default_classes/Actor.h"

class Wall : public Actor
{
public:
	Wall(const std::string& initSubtextureName,
		const glm::vec2& startPosition, const glm::vec2& startSize, const float startRotation);
	~Wall();
};