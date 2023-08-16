#include "TextureRender.h"
#include <iostream>

#include "../../main.h"

namespace Renderer
{
	Texture2D::Texture2D(const unsigned char* imageData, const GLuint width, const GLuint height,
		const GLuint channel, const GLenum wMode, const GLenum filter, const GLuint layer)
		: tex_width(width), tex_height(height), wrap_mode(wMode), tex_filter(filter)
	{
#ifdef OLD_VERSION
		glBindTexture(GL_TEXTURE_2D, 0);
		glGenTextures(1, &tex_id);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex_id);

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
		for (int i = 0; i < height * width; i++)
		{
			std::cout << (int)imageData[i];
		}
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_mode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_mode);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, tex_filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, tex_filter);
		glGenerateMipmap(GL_TEXTURE_2D);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glBindTexture(GL_TEXTURE_2D, 0);
#else
		glGenTextures(1, &tex_id);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D_ARRAY, tex_id);

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

		glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA8, width, height, 2);

		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, wrap_mode);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, wrap_mode);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, tex_filter);
		glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, tex_filter);

		for (int i = 0; i < 2; i++)
		{
			glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, height * i, width, height, 2, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
		}
		
		

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
#endif //OLD_VERSION
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
#ifdef OLD_VERSION
		glBindTexture(GL_TEXTURE_2D, tex_id);
#else
		glBindTexture(GL_TEXTURE_2D_ARRAY, tex_id);
#endif
	}

	void Texture2D::AddSubTexture(const std::string& name, const glm::vec2& posLeftBottomUV, const glm::vec2& posRightUpperUV, const GLuint& diffuse_layer)
	{
		sub_textures_map.emplace(name, SubTexture(posLeftBottomUV, posRightUpperUV, diffuse_layer));
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
