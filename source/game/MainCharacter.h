#pragma once

#include "Pawn.h"

class PlayerController;

namespace Game
{
	class MainCharacter: public Pawn
	{
	public:
		MainCharacter(std::shared_ptr<Renderer::Texture2D> texture, std::shared_ptr<Renderer::ShaderProgram> shader,
			const std::string& initSubtextureName,
			const float startMoveSpeed, const glm::vec2& startPosition = glm::vec2(0.f), const glm::vec2& startSize = glm::vec2(100.f, 100.f), const float startRotation = 0.f);

		//virtual void ChangeMoveVector(const glm::vec2& value) override;
		std::shared_ptr<PlayerController> GetPlayerController() { return player_controller; }

	protected:
		std::shared_ptr<PlayerController> player_controller;

		friend class PlayerController;
	};
}