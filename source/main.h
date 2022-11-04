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
class GameManager;

GameManager* GetWorld();

static glm::ivec2 window_size(1280, 720);