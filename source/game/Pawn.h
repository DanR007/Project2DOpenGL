#pragma once

#include "Actor.h"

class HealthComponent;


namespace Game
{
	class Pawn : public Actor
	{
	public:
		Pawn(std::shared_ptr<Renderer::Texture2D> texture, std::shared_ptr<Renderer::ShaderProgram> shader, const std::string& initSubtextureName,
			const glm::vec2& startPosition = glm::vec2(0.f), const glm::vec2& startSize = glm::vec2(1.f), const float startRotation = 0.f, const float moveSpeed = 0.f);
		Pawn() = delete;

		virtual void Update(float deltaTime) override;
		virtual void Move(const float deltaTime);
		virtual void ChangeMoveVector(const glm::vec2& value);

		void SetMoveSpeed(float speedValue) { move_speed = speedValue; }

		glm::vec2 GetMoveVector() { return move_vector; }

		virtual void DestroyActor() override { delete this; }

		~Pawn();
	protected:

		float move_speed;

		glm::vec2 move_vector = glm::vec2(0.f);

		
	private:

	};
}