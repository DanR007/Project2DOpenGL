#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

#define DEFAULT_VERTEX__SHADER_PATH "resources/shaders/defVertexShader.txt"
#define DEFAULT_FRAGMENT_SHADER_PATH "resources/shaders/defFragmentShader.txt"
#define TEXTURE_VERTEX_SHADER_PATH "resources/shaders/textureVertexShader.txt"
#define TEXTURE_FRAGMENT_SHADER_PATH "resources/shaders/textureFragmentShader.txt"
#define SPRITE_VERTEX_SHADER_PATH "resources/shaders/spriteVertexShader.txt"
#define SPRITE_FRAGMENT_SHADER_PATH "resources/shaders/spriteFragmentShader.txt"

glm::ivec2 window_size(1280, 720);


GLfloat triangle_coord[] =
{
	-0.5f, -0.5f, 0.f,
	-0.5f, 0.5f, 0.f,
	0.5f, 0.5f, 0.f,

	-0.5f, -0.5f, 0.f,
	0.5f, -0.5f, 0.f,
	0.5f, 0.5f, 0.f
};

GLfloat color_coord[] =
{
	-0.8f, 0.8f, 0.f,
	0.f, 0.8f, 0.f,
	-0.8f, 0.f,0.f
};

GLfloat texture_coordinates[] =
{
	0.f, 0.f,
	0.f, 1.f,
	1.f, 1.f,//если будет больше 1.f то текстура будет растянута

	0.f, 0.f,
	1.f, 0.f,
	1.f, 1.f
};