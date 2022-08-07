#pragma once

#include "Pawn.h"

namespace Game
{
	class MainCharacter: public Pawn
	{
	public:
		MainCharacter(std::shared_ptr<Renderer::AnimSprite> animSprite, const float startMoveSpeed, const glm::vec2& startPosition = glm::vec2(1.f), const glm::vec2& startSize = glm::vec2(100.f, 100.f), const float startRotation = 0.f);

		void Move(const glm::vec2& moveValue);
	};
}