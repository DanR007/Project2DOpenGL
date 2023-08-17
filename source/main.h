#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>

#include <memory>
#include <vector>

#include <iostream>

#include <cstdio>

//#define DEBUG_MEMORY
#define DEBUG

class Actor;
class Pawn;

class EngineManager;
class GameManager;

GameManager* GetWorld();
EngineManager* GetEngine();

static glm::ivec2 window_size(1280, 720);