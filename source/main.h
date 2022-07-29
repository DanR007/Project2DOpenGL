#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

glm::ivec2 window_size(1280, 720);

GLfloat triangle_coord[] =
{
	-0.5f, -0.5f, 0.f,
	0.f, 0.5f, 0.f,
	0.5f, -0.5f, 0.f
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
	0.f, 0.5f,
	1.f, 1.f
};