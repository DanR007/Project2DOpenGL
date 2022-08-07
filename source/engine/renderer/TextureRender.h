#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

#include <vector>
#include <map>
#include <string>

namespace Renderer
{
	class Texture2D
	{
	public:
		struct SubTexture
		{
			glm::vec2 left_bottom_UV, right_upper_UV;

			SubTexture()
				: left_bottom_UV(0.f), right_upper_UV(1.f)
			{

			}

			SubTexture(const glm::vec2& leftBottomUV, const glm::vec2& rightUpperUV)
				:left_bottom_UV(leftBottomUV), right_upper_UV(rightUpperUV)
			{

			}
		};


		Texture2D(const unsigned char* imageData, const GLuint width, 
			const GLuint height, const GLuint channel = 4,
			GLenum wMode = GL_CLAMP_TO_EDGE, const GLenum filter = GL_NEAREST);

		Texture2D() = delete;
		Texture2D& operator=(Texture2D&) = delete;

		Texture2D& operator=(Texture2D&& texture) noexcept;
		Texture2D(Texture2D&& texture) noexcept;

		~Texture2D();

		void Bind() const;

		GLuint GetHeight() const { return tex_height; }
		GLuint GetWidth() const { return tex_width; }

		void AddSubTexture(const std::string& name, const glm::vec2& posLeftBottom, const glm::vec2& posRightUpper);
		const SubTexture& GetSubTexture(const std::string& name);

	protected:
		
		GLuint tex_height, tex_width;
		GLenum wrap_mode, tex_filter;
		GLuint tex_id;

		std::map<std::string, SubTexture> sub_textures_map;
	};
}