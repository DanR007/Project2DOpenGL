#pragma once

#include <string>
#include <vector>
#include <memory>
#include <string>

#include <glm/vec2.hpp>

namespace Renderer
{
	class AnimSprite;
	class Texture2D;
	class ShaderProgram;
}


namespace Game
{
	class Actor
	{
	public:
		Actor(std::shared_ptr<Renderer::Texture2D> texture, std::shared_ptr<Renderer::ShaderProgram> shader,
			const std::string& initSubtexture,
			const glm::vec2& startPosition, const glm::vec2& startSize = glm::vec2(1.f), const float startRotation = 0.f);
		Actor(std::shared_ptr<Renderer::AnimSprite> animSprite, const glm::vec2& startPosition, const glm::vec2& startSize = glm::vec2(1.f), const float startRotation = 0.f);
		Actor() = delete;
		~Actor();


		virtual void Update(float deltaTime);

		std::shared_ptr<Renderer::AnimSprite> GetAnimSprite();

		glm::vec2 GetPosition() { return position; }
		glm::vec2 GetSize() { return size; }

		void SetPosition(const glm::vec2& newPosition);
		void SetSize(const glm::vec2& newSize);
		void SetRotation(const float newRotation);
	protected:
		glm::vec2 position, size;
		float rotation;

		std::unique_ptr<Renderer::AnimSprite> anim_sprite;
	};
}