#include "MainCharacter.h"

#include "../engine/renderer/AnimSprite.h"
#include "../engine/renderer/ShaderRender.h"
#include "../engine/renderer/TextureRender.h"

#include "../engine/managers/PhysicsManager.h"

#include "../engine/controllers/PlayerController.h"

#include "../main.h"

#include <iostream>

namespace Game
{
	MainCharacter::MainCharacter(std::shared_ptr<Renderer::Texture2D> texture, std::shared_ptr<Renderer::ShaderProgram> shader,
		const std::string& initSubtextureName, const float startMoveSpeed, const glm::vec2& startPosition, const glm::vec2& startSize, const float startRotation)
		:Pawn(std::move(texture), std::move(shader), initSubtextureName, startMoveSpeed, startPosition, startSize, startRotation)
	{
		player_controller = std::make_shared<PlayerController>(this, startMoveSpeed);
	}
}