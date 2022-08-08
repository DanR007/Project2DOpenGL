#include "Pawn.h"

#include "../engine/managers/ResourcesManager.h"

#include "../engine/renderer/AnimSprite.h"

namespace Game
{
	Pawn::Pawn(std::shared_ptr<Renderer::AnimSprite> animSprite,
		const float moveSpeed, const glm::vec2& startPosition, const glm::vec2& startSize, const float startRotation):
		Actor(animSprite, startPosition, startSize, startRotation)
	{
		move_speed = moveSpeed;
	}

	void Pawn::Move()
	{
		if(move_vector != glm::vec2(0.f, 0.f))
			anim_sprite->SetPosition(anim_sprite->GetPosition() + move_vector);
	}

	void Pawn::ChangeMoveVector(const glm::vec2& value)
	{
		move_vector += value;
	}

	void Pawn::Update(float deltaTime)
	{
		Move();
		Actor::Update(deltaTime);
	}

	Pawn::~Pawn()
	{

	}

}