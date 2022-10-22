#pragma once

#include "Actor.h"
#include "../../engine/managers/AI/AStar.h"

class HealthComponent;
class Controller;

namespace Game
{
	class Pawn : public Actor
	{
	public:
		Pawn(std::shared_ptr<Renderer::Texture2D> texture, std::shared_ptr<Renderer::ShaderProgram> shader, const std::string& initSubtextureName,
			const glm::vec2& startPosition = glm::vec2(0.f), const glm::vec2& startSize = glm::vec2(1.f), const float startRotation = 0.f, const float moveSpeed = 0.f);
		Pawn() = delete;

		void Update(float deltaTime) override;
		virtual void ChangeMoveVector(const glm::vec2& value);

		void SetMoveSpeed(float speedValue) { move_speed = speedValue; }

		glm::vec2 GetMoveVector() { return move_vector; }
		glm::vec2 GetMoveValue() { return _move_value; }
		~Pawn();
	protected:

		float move_speed;

		glm::vec2 move_vector = glm::vec2(0.f);
		glm::vec2 _move_value = glm::vec2(0.f);
		
		

		Controller* _controller;
	private:

	};
}