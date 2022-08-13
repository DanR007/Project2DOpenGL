#include "MainCharacter.h"

#include "../engine/renderer/AnimSprite.h"

#include "../engine/managers/PhysicsManager.h"

#include "../main.h"

#include <iostream>

namespace Game
{
	MainCharacter::MainCharacter(std::shared_ptr<Renderer::AnimSprite> animSprite, const float startMoveSpeed, const glm::vec2& startPosition, const glm::vec2& startSize, const float startRotation)
		:Pawn(animSprite, startMoveSpeed, startPosition, startSize, startRotation)
	{
	}
	
	void MainCharacter::Move(const float deltaTime)
	{
		if (move_vector != glm::vec2(0.f, 0.f) && PhysicsManager::CanMove(std::move(all_actors), GetPosition() + move_vector, GetSize()))
		{
			for (std::shared_ptr<Game::Actor> actor : all_actors)
			{
				actor->SetPosition(actor->GetPosition() - move_vector);
			}
		}
	}
}