#include "Pawn.h"

#include "../managers/PhysicsManager.h"
#include "../managers/GameManager.h"

#include "../renderer/AnimSprite.h"
#include "../renderer/ShaderRender.h"
#include "../renderer/TextureRender.h"

#include "../controllers/Controller.h"

#include "../../main.h"

namespace Game
{
	Pawn::Pawn(const std::string& initSubtextureName,
		const glm::vec2& startPosition, const glm::vec2& startSize, const float startRotation):
		Actor(initSubtextureName, startPosition, startSize, startRotation)
	{
		
	}

	Pawn::Pawn(Pawn&& p) noexcept
		:Actor(std::move(p))
	{
		delete _controller;

		_controller = p._controller;
	}

	void Pawn::Update(float deltaTime)
	{
		_controller->Move(deltaTime);
		Actor::Update(deltaTime);
	}

	Pawn::~Pawn()
	{
		if (_controller)
		{
			delete _controller;
			_controller = nullptr;
		}
	}
}