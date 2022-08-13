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
		Pawn(std::shared_ptr<Renderer::AnimSprite> animSprite,
			const float moveSpeed, const glm::vec2& startPosition, const glm::vec2& startSize = glm::vec2(1.f), const float startRotation = 0.f);
		Pawn() = delete;

		virtual void Move(const float deltaTime);
		virtual void ChangeMoveVector(const glm::vec2& value);
		virtual void Update(float deltaTime) override;

		~Pawn();
	protected:

		float move_speed;
		glm::vec2 move_vector = glm::vec2(0.f, 0.f);
	};
}