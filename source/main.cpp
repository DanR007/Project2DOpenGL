#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

#include "main.h"
#include "AllTestCases.h"

#include "engine/managers/ResourcesManager.h"
#include "engine/managers/EngineManager.h"
#include "engine/managers/RenderManager.h"

#include "engine/controllers/PlayerController.h"

#include <cstdio>
#include <iostream>
#include <time.h>
#include <chrono>
#include <thread>

#include "engine/renderer/AnimSprite.h"
#include "engine/renderer/ShaderRender.h"
#include "engine/renderer/TextureRender.h"

#include "engine/UI/Widget.h"
#include "engine/UI/Text.h"

//#define TEST_CASES
#define PHYSIC_TESTS
#define GAMEPLAY_TESTS
//#define NAVMESH_TESTS
#define PLAY_IN_EDITOR

EngineManager* engine = nullptr;

GameManager* GetWorld() { return engine->GetWorld(); }
EngineManager* GetEngine() { return engine; }

bool game_start = false;

void* operator new(std::size_t size)
{
	void* n = malloc(size);
	if (n)
	{
#ifdef DEBUG_MEMORY
		if(game_start)
			printf("Called new: %p\n", n);
#endif
		//std::cout << "Called new: " << n << std::endl;
		return n;
	}
	else
	{
		std::bad_alloc ba;
		std::cout << "Error memory alloc\n";
		throw ba;
	}
}

void* operator new[](std::size_t size)
{
	void* n = malloc(size);
	if (n)
	{
#ifdef DEBUG_MEMORY
		if (game_start)
			printf("Called new[]: %p\n", n);
#endif
		//std::cout << "Called new: " << n << std::endl;
		return n;
	}
	else
	{
		std::bad_alloc ba;
		std::cout << "Error memory alloc\n";
		throw ba;
	}
}
void operator delete(void* ptr)
{
#ifdef DEBUG_MEMORY
	if(game_start)
		printf("Called deleted: %p\n", ptr);
#endif
	free(ptr);
}
void operator delete[](void* ptr)
{
#ifdef DEBUG_MEMORY
	if (game_start)
		printf("Called deleted[]: %p\n", ptr);
#endif
	free(ptr);
}

void glfwWindowSizeCallback(GLFWwindow* currentWindow, int size_x, int size_y)
{
	window_size.x = size_x;
	window_size.y = size_y;
	glViewport(0, 0, window_size.x, window_size.y);
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
	GLFWwindow* window = nullptr;

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

		glClearColor(0.5f, 0.5f, 0.5f, 1.f);

		game_start = true;

		auto lastTime = std::chrono::steady_clock::now();

		Widget* wdg = new Widget();
		Text* t = wdg->AddElement<Text>(glm::vec2(0), glm::vec2(35.f));
		t->SetText("ab " + std::to_string(10));

		while (!glfwWindowShouldClose(window))
		{

			glClear(GL_COLOR_BUFFER_BIT);
			auto currentTime = std::chrono::steady_clock::now();
			float duration = float(double(std::chrono::steady_clock::duration(currentTime - lastTime).count()) / 1e9);
			lastTime = currentTime;

			engine->Update(duration);

			glfwSwapBuffers(window);
			glfwPollEvents();

		}
#endif // PLAY_IN_EDITOR
	}
	//delete window;
	delete engine;
	glfwTerminate();
	_CrtDumpMemoryLeaks();
	return 0;
}