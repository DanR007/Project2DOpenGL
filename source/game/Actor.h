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


namespace Game
{
	class Actor
	{
	public:
		Actor(std::shared_ptr<Renderer::Texture2D> texture, std::shared_ptr<Renderer::ShaderProgram> shader, const std::string& subtextureName,
			const glm::vec2& startPosition, const glm::vec2& startSize = glm::vec2(1.f), const float startRotation = 0.f);
		Actor() = delete;
		~Actor();

		virtual void Draw();
		virtual void Update(float deltaTime);

		Renderer::AnimSprite* GetAnimSprite();
	protected:
		glm::vec2 position, size;
		float rotation;

		Renderer::AnimSprite* anim_sprite;
	};
}