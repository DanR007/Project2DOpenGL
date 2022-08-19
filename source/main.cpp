#include "main.h"

#include "engine/managers/ResourcesManager.h"
#include "engine/managers/GameManager.h"

#include "game/MainCharacter.h"

#include <iostream>
#include <time.h>
#include <chrono>
#include <thread>

std::string ResourcesManager::exe_path;

ShaderProgramMap ResourcesManager::shader_program_map;
TexturesMap ResourcesManager::textures_map;
SpritesMap ResourcesManager::sprites_map;
AnimSpritesMap ResourcesManager::anim_sprites_map;

void glfwWindowSizeCallback(GLFWwindow* currentWindow, int size_x, int size_y)
{
	window_size.x = size_x;
	window_size.y = size_y;
	glViewport(0, 0, window_size.x, window_size.y);
}

void glfwKeyCallback(GLFWwindow* currentWindow, int key, int scancode, int action, int mode)
{
	main_character->Input(currentWindow, key, scancode, action, mode);
}

int main(int argc, char** argv)
{
	GLFWwindow* window;
	
	if (!glfwInit())
	{
		std::cerr << "GLFW does not work correct or cant open idk" << std::endl;
		return -1;
	}
	{
		window = glfwCreateWindow(window_size.x, window_size.y, "Platformer2D", NULL, NULL);

		if (!window)
		{
			std::cerr << "Cant create a window" << std::endl;
			glfwTerminate();
			return -1;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		glfwSetWindowSizeCallback(window, glfwWindowSizeCallback);
		glfwSetKeyCallback(window, glfwKeyCallback);

		glfwMakeContextCurrent(window);

		if (!gladLoadGL())
		{
			std::cerr << "GLAD does not exist or cant open" << std::endl;
			return -1;
		}

		ResourcesManager::LoadAll(*argv);
		GameManager::BeginPlay();

		glClearColor(1.f, 1.f, 1.f, 1.f);

		
		//textureAtlas - texture name
		//names - vector of names subtextures

		

		auto lastTime = std::chrono::high_resolution_clock::now();
		while (!glfwWindowShouldClose(window))
		{
			glClear(GL_COLOR_BUFFER_BIT);

			auto currentTime = std::chrono::high_resolution_clock::now();
			float duration = float(double(std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - lastTime).count()) / 1e9);
			lastTime = currentTime;

			GameManager::Update(duration);

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

	return 0;
}