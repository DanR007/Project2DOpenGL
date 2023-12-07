#pragma once

#include "../../../engine/default_classes/Actor.h"

class Ground : public Actor
{
public:
	Ground(const glm::ivec2& position);
	virtual ~Ground();

private:
    Ground(const std::string& initSubtextureName,
	const glm::vec2& startPosition, const glm::vec2& startSize, const uint8_t& render_layer);
};