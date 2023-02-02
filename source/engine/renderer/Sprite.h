#pragma once

#include <memory>
#include <string>
#include <vector>

#include <glad/glad.h>

#define DYNAMIC

#include "../default_classes/Component.h"

namespace Renderer
{
	class ShaderProgram;
	class Texture2D;

	class Sprite  : public MovableComponent
	{
	public:
		Sprite(std::shared_ptr<Texture2D> texture, std::shared_ptr <ShaderProgram> shader, 
			const std::string& initialSubtextureName, Game::Actor* owner = nullptr, const glm::vec2& position = glm::vec2(0.f), 
			const glm::vec2& size = glm::vec2(1.f), const float rotation = 0.f);
		~Sprite();

		Sprite(const Sprite&) = delete;
		Sprite& operator=(const Sprite&) = delete;

		void SetNewSprite(const std::string& newSubtextureName);

		inline std::shared_ptr<Renderer::ShaderProgram> GetShaderProgram() const { return _shader; }
		inline std::shared_ptr<Renderer::Texture2D> GetTexture() const { return _texture; }

		virtual void Render() const;
	protected:
		std::shared_ptr<Texture2D> _texture;
		std::shared_ptr<ShaderProgram> _shader;

		std::string _subtexture_name;

		GLuint _vertex_array_objects, texture_coord_buffer, vertex_coord_buffer, vertex_element_buffer;
	};
}