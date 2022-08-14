#include "Pawn.h"

#include "../engine/managers/PhysicsManager.h"

#include "../engine/renderer/AnimSprite.h"
#include "../engine/renderer/ShaderRender.h"
#include "../engine/renderer/TextureRender.h"

#include "../engine/controllers/Controller.h"

#include "../main.h"

namespace Game
{
	Pawn::Pawn(std::shared_ptr<Renderer::Texture2D> texture, std::shared_ptr<Renderer::ShaderProgram> shader, const std::string& initSubtextureName,
		const float moveSpeed, const glm::vec2& startPosition, const glm::vec2& startSize, const float startRotation):
		Actor(std::move(texture), std::move(shader), initSubtextureName, startPosition, startSize, startRotation)
	{
		controller = std::make_shared<Controller>(this, moveSpeed);
	}

	void Pawn::Update(float deltaTime)
	{
		controller->Move(deltaTime);
		Actor::Update(deltaTime);
	}

	Pawn::~Pawn()
	{

	}

}