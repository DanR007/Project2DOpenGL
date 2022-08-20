#include "Pawn.h"

#include "../engine/managers/PhysicsManager.h"
#include "../engine/managers/GameManager.h"

#include "../engine/renderer/AnimSprite.h"
#include "../engine/renderer/ShaderRender.h"
#include "../engine/renderer/TextureRender.h"

#include "../engine/controllers/Controller.h"

#include "../main.h"

namespace Game
{
	Pawn::Pawn(std::shared_ptr<Renderer::Texture2D> texture, std::shared_ptr<Renderer::ShaderProgram> shader, const std::string& initSubtextureName,
		const glm::vec2& startPosition, const glm::vec2& startSize, const float startRotation, const float moveSpeed):
		Actor(std::move(texture), std::move(shader), initSubtextureName, startPosition, startSize, startRotation)
	{
		move_speed = moveSpeed;
	}

	void Pawn::Update(float deltaTime)
	{
		Move(deltaTime);
		Actor::Update(deltaTime);
	}

	Pawn::~Pawn()
	{

	}

	void Pawn::Move(float deltaTime)
	{
		if (move_vector != glm::vec2(0.f, 0.f) && 
			PhysicsManager::CanMove(this, _position + move_vector * deltaTime * move_speed))
			SetPosition(_position + move_vector * deltaTime * move_speed);
	}

	void Pawn::ChangeMoveVector(const glm::vec2& inputVector)
	{
		move_vector += inputVector;
	}
}