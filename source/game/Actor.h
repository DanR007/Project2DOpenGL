#pragma once

#include <string>
#include <vector>
#include <memory>

#include <glm/vec2.hpp>

namespace Renderer
{
	class Sprite;
	class Texture2D;
	class ShaderProgram;
}


namespace Game
{
	class Actor
	{
	public:
		Actor(std::shared_ptr<Renderer::Texture2D> texture, std::shared_ptr<Renderer::ShaderProgram> shader, const std::string& initSpriteName,
			const glm::vec2& startPosition, const glm::vec2& startSize = glm::vec2(1.f), const float startRotation = 0.f);
		~Actor();

		void Draw();
	protected:
		Renderer::Sprite* sprite;

		glm::vec2 position, size;
		float rotation;

	};
}