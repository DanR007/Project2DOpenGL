#include "Pawn.h"

#include "../engine/managers/ResourcesManager.h"


namespace Game
{
	Pawn::Pawn(std::shared_ptr<Renderer::AnimSprite> animSprite,
		const float moveSpeed, const glm::vec2& startPosition, const glm::vec2& startSize, const float startRotation):
		Actor(animSprite, startPosition, startSize, startRotation)
	{
		move_speed = moveSpeed;
	}

	Pawn::~Pawn()
	{

	}

}