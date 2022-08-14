#pragma once

#include "Actor.h"

class Controller;

namespace Game
{
	class Pawn : public Actor
	{
	public:
		Pawn(std::shared_ptr<Renderer::Texture2D> texture, std::shared_ptr<Renderer::ShaderProgram> shader, const std::string& initSubtextureName,
			const float moveSpeed, const glm::vec2& startPosition = glm::vec2(0.f), const glm::vec2& startSize = glm::vec2(1.f), const float startRotation = 0.f);
		Pawn() = delete;

		virtual void Update(float deltaTime) override;

		~Pawn();
	protected:
		std::shared_ptr<Controller> controller;

		friend class Controller;
	};
}