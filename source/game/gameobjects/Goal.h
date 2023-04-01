#pragma once
#include "../../engine/default_classes/Actor.h"

class Goal : public Game::Actor
{
public:
	Goal(std::shared_ptr<Renderer::Texture2D> texture, std::shared_ptr<Renderer::ShaderProgram> shader,
		const std::string& initSubtextureName,
		const glm::vec2& startPosition, const glm::vec2& startSize, const float startRotation);
};