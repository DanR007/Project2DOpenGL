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
	Pawn::Pawn(std::shared_ptr<Renderer::Texture2D> texture, std::shared_ptr<Renderer::ShaderProgram> shader, const std::string& initSubtextureName,
		const glm::vec2& startPosition, const glm::vec2& startSize, const float startRotation, const float moveSpeed):
		Actor(std::move(texture), std::move(shader), initSubtextureName, startPosition, startSize, startRotation)
	{
		move_speed = moveSpeed;
		_controller = new Controller(this, moveSpeed);
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

	void Pawn::ChangeMoveVector(const glm::vec2& inputVector)
	{
		move_vector += inputVector;
	}
}