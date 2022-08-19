#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

#include <memory>
#include <vector>



namespace Game
{
	class Actor;
	class Pawn;
}

static glm::ivec2 window_size(1280, 720);

const glm::vec2 right_vector = glm::vec2(1.f, 0.f);
const glm::vec2 up_vector = glm::vec2(0.f, 1.f);

/*GLfloat triangle_coord[] =
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
};*/