#include "MainCharacter.h"

#include "../engine/renderer/AnimSprite.h"

namespace Game
{
	MainCharacter::MainCharacter(std::shared_ptr<Renderer::AnimSprite> animSprite, const float startMoveSpeed, const glm::vec2& startPosition, const glm::vec2& startSize, const float startRotation)
		:Pawn(animSprite, startMoveSpeed, startPosition, startSize, startRotation)
	{
	}
	
	/*void MainCharacter::Move(const glm::vec2& moveVector)
	{
		anim_sprite->SetPosition(anim_sprite->GetPosition() + moveVector);
	}*/
}