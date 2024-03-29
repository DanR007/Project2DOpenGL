#pragma once

#include <stdio.h>

#include <memory>
#include <string>
#include <vector>

#include <glad/glad.h>

#include "../default_classes/Component.h"

namespace Renderer
{
	class ShaderProgram;
	class Texture2D;

	class RenderImage
	{
	public:
		/*render_layer for static game actors is 0, for dynamic 1, for UI background is 2, for text and images 3*/
		RenderImage(std::shared_ptr<Texture2D> texture, std::shared_ptr <ShaderProgram> shader, 
			const std::string& initialSubtextureName, const uint8_t& render_layer);
		~RenderImage();

		void SetNewImage(const std::string& newSubtextureName);

		inline GLuint GetVAO() { return _vertex_array_object; };
		inline Texture2D* GetTexture() { return _texture.get(); }
		inline ShaderProgram* GetShader() { return _shader.get(); }
		inline uint8_t GetRenderLayer() const { return _render_layer; }
		inline std::string GetSpriteName() const { return _subtexture_name; }


		GLuint GetDiffuseLayer() const;
		bool operator==(const RenderImage& right) 
		{
			return _subtexture_name == right._subtexture_name;
		}
		bool operator!=(const RenderImage& right) 
		{
			return _subtexture_name != right._subtexture_name;
		}
		bool operator<(const RenderImage& right) 
		{
			return GetRenderLayer() < right.GetRenderLayer();
		}
	private:
		std::shared_ptr<Texture2D> _texture;
		std::shared_ptr<ShaderProgram> _shader;

		std::string _subtexture_name;
	public:
		GLuint _vertex_array_object, _texture_buffer_object, _vertex_buffer_object, _element_buffer_object;

		uint8_t _render_layer;
	};

	

	class Sprite : public Component
	{
	public:
		Sprite(Renderer::RenderImage* image,
			Object* owner = nullptr, const glm::vec2& position = glm::vec2(0.f),
			const glm::vec2& size = glm::vec2(1.f), const float rotation = 0.f);

		virtual ~Sprite();

		Sprite(const Sprite&) = delete;
		Sprite& operator=(const Sprite&) = delete;

		void SetNewSprite(const std::string& newSubtextureName);
		inline void SetRenderImage(RenderImage* img) { _image = img; }

		inline RenderImage* GetRenderImage() { return _image; }

		bool InView() const;

		bool GetNeedToRender() 
		{
			return InView() && _need_to_render;
		}

		inline void SetNeedToRender(const bool& need_to_render) { _need_to_render = need_to_render; }
	protected:
		bool _need_to_render = true;
		RenderImage* _image;

		std::string _subtexture_name;
	};
}

