#pragma once

#include <string>
#include <vector>
#include <memory>

#include <glm/vec2.hpp>

namespace Renderer
{
	class AnimSprite;
	class Texture2D;
	class ShaderProgram;
}
namespace Physics
{
	class Collider;
}

namespace Game
{
	class Actor
	{
	public:
		Actor(std::shared_ptr<Renderer::Texture2D> texture, std::shared_ptr<Renderer::ShaderProgram> shader,
			const std::string& initSubtextureName,
			const glm::vec2& startPosition, const glm::vec2& startSize = glm::vec2(1.f), const float startRotation = 0.f);

		Actor() = delete;
		~Actor();

		virtual void Update(float deltaTime);
		virtual void BeginPlay();

		std::shared_ptr<Renderer::AnimSprite> GetAnimSprite();
		std::shared_ptr<Physics::Collider> GetCollider() { return _collider; }

		void SetCollider(std::shared_ptr<Physics::Collider> collider) { _collider = collider; }

		glm::vec2 GetPosition() { return _position; }

		void SetPosition(const glm::vec2& newPosition);
		void SetSize(const glm::vec2& newSize);
		void SetRotation(const float newRotation);
		void SetIterator(std::vector<std::shared_ptr<Game::Actor>>::iterator iterator) { _iterator = iterator; }

		void AddWorldPosition(const glm::vec2& value);

		void AddAnimState(const std::string& stateName, std::vector<std::pair<std::string, float>> subTextureDuration);
		void PlayAnim(const std::string& stateName);

		void DestroyActor();

	protected:
		glm::vec2 _position;
		float _rotation;

		std::vector<std::shared_ptr<Game::Actor>>::iterator _iterator;

		std::unique_ptr<Renderer::AnimSprite> _anim_sprite;
		std::shared_ptr<Physics::Collider> _collider;
	};
}