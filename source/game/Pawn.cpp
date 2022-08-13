#include "Pawn.h"

#include "../engine/managers/ResourcesManager.h"
#include "../engine/managers/PhysicsManager.h"

#include "../engine/renderer/AnimSprite.h"

#include "../main.h"

namespace Game
{
	Pawn::Pawn(std::shared_ptr<Renderer::AnimSprite> animSprite,
		const float moveSpeed, const glm::vec2& startPosition, const glm::vec2& startSize, const float startRotation):
		Actor(animSprite, startPosition, startSize, startRotation)
	{
		move_speed = moveSpeed;
	}

	void Pawn::Move(const float deltaTime)
	{
		if(move_vector != glm::vec2(0.f, 0.f) && PhysicsManager::CanMove(all_actors, position + move_vector * deltaTime * move_speed, size))
			SetPosition(position + move_vector * deltaTime * move_speed);
	}

	void Pawn::ChangeMoveVector(const glm::vec2& value)
	{
		move_vector += value;
	}

	void Pawn::Update(float deltaTime)
	{
		Move(deltaTime);
		Actor::Update(deltaTime);
	}

	Pawn::~Pawn()
	{

	}

}