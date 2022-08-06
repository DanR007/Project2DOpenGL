#include "Pawn.h"

#include "../engine/managers/ResourcesManager.h"


namespace Game
{
	Pawn::Pawn(std::shared_ptr<Renderer::Texture2D> texture, std::shared_ptr<Renderer::ShaderProgram> shader, const std::string& initSubtextureName,
		const float moveSpeed, const glm::vec2& startPosition, const glm::vec2& startSize, const float startRotation):
		Actor(texture, shader, initSubtextureName, startPosition, startSize, startRotation)
	{
		move_speed = moveSpeed;
	}

	Pawn::~Pawn()
	{
		delete anim_sprite;
		anim_sprite = nullptr;
	}

}