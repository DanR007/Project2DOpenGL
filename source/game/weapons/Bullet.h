#pragma once

#include "../../engine/default_classes/Actor.h"

#include <memory>

#include <glm/vec2.hpp>

namespace Renderer
{
	class Texture2D;
	class ShaderProgram;
	class Sprite;
}
namespace Game
{
	class Bullet : public Actor
	{
	public:
		Bullet(std::shared_ptr<Renderer::Texture2D> texture, std::shared_ptr<Renderer::ShaderProgram> shader,
			const std::string& initSubtextureName,
			const glm::vec2& startPosition, const glm::vec2& startSize = glm::vec2(1.f), const float startRotation = 0.f);

		~Bullet(){}

		void SetSpeed(float speed) { _speed = speed; }
		void SetDamage(int damage) { _damage = damage; }
		void SetMoveVector(const glm::vec2& moveVector) { _move_vector = moveVector; }

		virtual void Update(float deltaTime) override;

		//virtual void DestroyActor() override { delete this; }
	protected:
		glm::vec2 _move_vector;
		float _speed;
		int _damage;
	};
}