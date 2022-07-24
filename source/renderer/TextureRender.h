#pragma once

#include <GLFW/glfw3.h>

#include <string>

namespace Renderer
{
	class Texture2D
	{
	public:

		Texture2D(const unsigned char* image_data, int width, int height, int channel);

		Texture2D() = delete;
		Texture2D& operator=(Texture2D&) = delete;

		Texture2D& operator=(Texture2D&& texture);
		Texture2D(Texture2D&& texture);

		~Texture2D();


	private:
		
		GLuint tex_id;
	};
}