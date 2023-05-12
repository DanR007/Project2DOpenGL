#include "main.h"
#include "AllTestCases.h"

#include "engine/managers/ResourcesManager.h"
#include "engine/managers/EngineManager.h"
#include "engine/managers/RenderManager.h"

#include "engine/controllers/PlayerController.h"

#include <iostream>
#include <time.h>
#include <chrono>
#include <thread>

#include "engine/renderer/AnimSprite.h"
#include "engine/renderer/ShaderRender.h"
#include "engine/renderer/TextureRender.h"

//#define TEST_CASES
#define PHYSIC_TESTS
#define GAMEPLAY_TESTS
//#define NAVMESH_TESTS
#define PLAY_IN_EDITOR

//uniform mat4 modelMat;

std::string ResourcesManager::exe_path;

ShaderProgramMap ResourcesManager::shader_program_map;
TexturesMap ResourcesManager::textures_map;

EngineManager* engine = nullptr;

GameManager* GetWorld() { return engine->GetWorld(); }
EngineManager* GetEngine() { return engine; }

void glfwWindowSizeCallback(GLFWwindow* currentWindow, int size_x, int size_y)
{
	window_size.x = size_x;
	window_size.y = size_y;
	glViewport(0, 0, window_size.x, window_size.y);
	
	std::cout << window_size.x << " " << window_size.y << std::endl;
}

void glfwKeyCallback(GLFWwindow* currentWindow, int key, int scancode, int action, int mode)
{
	PlayerController* controller = GetWorld()->GetPlayerController();
	if(controller)
		controller->InputKeyboard(currentWindow, key, scancode, action, mode);
}

void glfwMouseButtonCallback(GLFWwindow* currentWindow, int button, int action, int mode)
{
	PlayerController* controller = GetWorld()->GetPlayerController();
	if(controller)
		controller->InputMouse(currentWindow, button, action, mode);
}

void glfwCursorPosCallback(GLFWwindow* currentWindow, double xPos, double yPos)
{
	PlayerController* controller = GetWorld()->GetPlayerController();
	if (controller)
		controller->CursorMove(currentWindow, xPos, yPos);
}

int main(int argc, char** argv)
{
	bool is_debuging = false;
#ifdef DEBUG
	is_debuging = true;

#endif//DEBUG
	GLFWwindow* window;
	
	if (!glfwInit())
	{
		std::cerr << "GLFW does not work correct or cant open idk" << std::endl;
		return -1;
	}
	{
		window = glfwCreateWindow(window_size.x, window_size.y, "Strategy2D", is_debuging ? nullptr : glfwGetPrimaryMonitor(), NULL);

		if (!window)
		{
			std::cerr << "Can't create a window" << std::endl;
			glfwTerminate();
			return -1;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		glfwSetWindowSizeCallback(window, glfwWindowSizeCallback);
		glfwSetKeyCallback(window, glfwKeyCallback);
		glfwSetMouseButtonCallback(window, glfwMouseButtonCallback);
		glfwSetCursorPosCallback(window, glfwCursorPosCallback);

		glfwMakeContextCurrent(window);

		if (!gladLoadGL())
		{
			std::cerr << "GLAD does not exist or cant open" << std::endl;
			return -1;
		}

		engine = new EngineManager(argv);
#ifdef TEST_CASES
#ifdef PHYSIC_TESTS
		PlayPhysicsTestCases();
#endif//PHYSIC_TESTS
#ifdef GAMEPLAY_TESTS

#endif//GAMEPLAY_TESTS
#ifdef NAVMESH_TESTS
		PlayNavMeshTests();
#endif

#endif // TEST_CASES
#ifdef PLAY_IN_EDITOR
		engine->Begin();

		glClearColor(0.9f, 0.9f, 0.9f, 1.f);

		auto lastTime = std::chrono::high_resolution_clock::now();
		while (!glfwWindowShouldClose(window))
		{
			glClear(GL_COLOR_BUFFER_BIT);

			auto currentTime = std::chrono::high_resolution_clock::now();
			float duration = float(double(std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - lastTime).count()) / 1e9);
			lastTime = currentTime;

			engine->Update(duration);

			//world->Update(duration);
			//std::thread physics_thread(&Physics::PhysicsManager::Update, world->GetPhysicsManager());

			glfwSwapBuffers(window);
			glfwPollEvents();

			//physics_thread.join();
		}
#endif // PLAY_IN_EDITOR
	}

	return 0;
}