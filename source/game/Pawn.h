#pragma once

#include "Actor.h"

namespace Renderer
{
	class AnimSprite;
}

namespace Game
{
	class Pawn : public Actor
	{
	public:
		Pawn(std::shared_ptr<Renderer::Texture2D> texture, std::shared_ptr<Renderer::ShaderProgram> shader, const std::string& initSubtextureName,
			const float moveSpeed, const glm::vec2& startPosition, const glm::vec2& startSize = glm::vec2(1.f), const float startRotation = 0.f);
		Pawn() = delete;

		~Pawn();
	protected:

		float move_speed;
	};
}