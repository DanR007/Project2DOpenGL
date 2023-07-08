#pragma once

#include <memory>
#include <string>
#include <vector>

#include <glad/glad.h>

#include "../default_classes/Component.h"

#include "../Delegate.h"

namespace Renderer
{
	class ShaderProgram;
	class Texture2D;

	class RenderImage
	{
	public:
		RenderImage(std::shared_ptr<Texture2D> texture, std::shared_ptr <ShaderProgram> shader, const std::string& initialSubtextureName);
		~RenderImage();

		void SetNewImage(const std::string& newSubtextureName);

		inline GLuint GetVAO() { return _vertex_array_object; };
		Texture2D* GetTexture() { return _texture.get(); }
		ShaderProgram* GetShader() { return _shader.get(); }
	private:
		std::shared_ptr<Texture2D> _texture;
		std::shared_ptr<ShaderProgram> _shader;

		std::string _subtexture_name;
	public:
		GLuint _vertex_array_object, _texture_buffer_object, _vertex_buffer_object, _element_buffer_object;
	};

	class Sprite : public MovableComponent
	{
	public:
		Sprite(Renderer::RenderImage* image,
			Actor* owner = nullptr, const glm::vec2& position = glm::vec2(0.f),
			const glm::vec2& size = glm::vec2(1.f), const float rotation = 0.f);

		virtual ~Sprite();

		Sprite(const Sprite&) = delete;
		Sprite& operator=(const Sprite&) = delete;

		void SetNewSprite(const std::string& newSubtextureName);

		inline RenderImage* GetRenderImage() { return _image; }

		bool InView() const;

		bool GetNeedToRender() {
			return InView() && _need_to_render;
		}

		inline void SetNeedToRender(const bool& need_to_render) { _need_to_render = need_to_render; }
	protected:
		bool _need_to_render = true;
		RenderImage* _image;

		std::string _subtexture_name;
	};
}