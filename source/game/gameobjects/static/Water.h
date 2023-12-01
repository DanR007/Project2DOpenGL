#pragma once

#include "../../../engine/default_classes/Actor.h"

class Water : public Actor
{
public:
	Water(const glm::ivec2& position);
	virtual ~Water();

private:
    Water(const std::string& initSubtextureName,
	const glm::vec2& startPosition, const glm::vec2& startSize, const uint8_t& render_layer);

};