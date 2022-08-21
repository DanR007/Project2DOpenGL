#include "TextureRender.h"
#include <iostream>

namespace Renderer
{
	Texture2D::Texture2D(const unsigned char* imageData, const GLuint width, const GLuint height,
		const GLuint channel, const GLenum wMode, const GLenum filter)
		: tex_width(width), tex_height(height), wrap_mode(wMode), tex_filter(filter)
	{
		glGenTextures(1, &tex_id);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex_id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_mode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_mode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, tex_filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, tex_filter);
		glGenerateMipmap(GL_TEXTURE_2D);

		GLenum format;

		switch (channel)
		{
		case 3:
			format = GL_RGB;
			break;
		case 4:
			format = GL_RGBA;
			break;
		default:
			format = GL_RGBA;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, format, tex_width, tex_height, 0, format, GL_UNSIGNED_BYTE, imageData);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture2D& Texture2D::operator=(Texture2D&& texture) noexcept
	{
		glDeleteTextures(1, &tex_id);
		tex_id = texture.tex_id;
		tex_height = texture.tex_height;
		tex_width = texture.tex_width;
		tex_filter = texture.tex_filter;
		wrap_mode = texture.wrap_mode;

		texture.tex_id = 0;

		return *this;
	}

	Texture2D::Texture2D(Texture2D&& texture) noexcept
	{
		tex_id = texture.tex_id;
		tex_height = texture.tex_height;
		tex_width = texture.tex_width;
		tex_filter = texture.tex_filter;
		wrap_mode = texture.wrap_mode;

		texture.tex_id = 0;
	}

	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &tex_id);
	}

	void Texture2D::Bind() const
	{
		glBindTexture(GL_TEXTURE_2D, tex_id);
	}

	void Texture2D::AddSubTexture(const std::string& name, const glm::vec2& posLeftBottomUV, const glm::vec2& posRightUpperUV)
	{
		sub_textures_map.emplace(name, SubTexture(posLeftBottomUV, posRightUpperUV));
	}

	const Texture2D::SubTexture& Texture2D::GetSubTexture(const std::string& name)
	{
		auto it = sub_textures_map.find(name);

		if (it == sub_textures_map.end())
		{
			std::cerr << "Cant find subtexture: " + name << std::endl;
			return SubTexture(); //return default sub texture
		}

		return it->second;
	}
}
