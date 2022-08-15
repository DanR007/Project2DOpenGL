#include "main.h"
#include "engine/managers/ResourcesManager.h"
#include "engine/managers/PhysicsManager.h"

#include "engine/renderer/ShaderRender.h"
#include "engine/renderer/TextureRender.h"
#include "engine/renderer/AnimSprite.h"

#include "engine/controllers/PlayerController.h"

#include "game/Actor.h"
#include "game/Pawn.h"
#include "game/MainCharacter.h"

#include "game/enemies/MeleeEnemy.h"

#include "game/gameobjects/WallActor.h"

#include <iostream>
#include <time.h>
#include <chrono>

std::vector<Game::Pawn*> pawns;
std::shared_ptr<Game::MainCharacter> main_character;
std::vector<std::shared_ptr<Game::Actor>> all_actors;

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
		ResourcesManager manager = ResourcesManager(*argv);

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

		//std::shared_ptr<Renderer::ShaderProgram> defShader = manager.LoadShaderPrograms("default", DEFAULT_FRAGMENT_SHADER_PATH, DEFAULT_VERTEX__SHADER_PATH);
		auto textureShader = manager.LoadShaderPrograms("texture", TEXTURE_FRAGMENT_SHADER_PATH, TEXTURE_VERTEX_SHADER_PATH);
		auto spriteShader = manager.LoadShaderPrograms("spriteShader", SPRITE_FRAGMENT_SHADER_PATH, SPRITE_VERTEX_SHADER_PATH);

		glClearColor(1.f, 1.f, 1.f, 1.f);

		std::vector<std::string> names = { "mush1", "mush2", "mush3", "wall"};
		
		manager.LoadTextureAtlas("textureAtlas", "resources/textures/mushroom.png", names, 16, 16);
		//textureAtlas - texture name
		//names - vector of names subtextures

		glm::vec2 mainCharacterSize = glm::ivec2(100, 100);
		main_character = std::make_shared<Game::MainCharacter>(std::move(manager.GetTexture("textureAtlas")), std::move(manager.GetShaderProgram("spriteShader")), "mush1", 100.f,
			glm::vec2(window_size.x / 2 - mainCharacterSize.x / 2, window_size.y / 2 - mainCharacterSize.y / 2), mainCharacterSize);

		glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(window_size.x), 0.f, static_cast<float>(window_size.y), -100.f, 100.f);
		manager.GetShaderProgram("spriteShader")->Use();
		manager.GetShaderProgram("spriteShader")->SetIn("tex", 0);
		manager.GetShaderProgram("spriteShader")->SetMatrix4("projectionMat", projectionMatrix);

		std::vector<std::pair<std::string, float>> stateDuration =
		{
			std::make_pair(std::string("mush1"), 1.f),
			std::make_pair(std::string("mush2"), 1.f),
			std::make_pair(std::string("mush3"), 1.f)
		};

		main_character->AddAnimState("walk", stateDuration);
		main_character->PlayAnim("walk");
		main_character->BeginPlay();
		//all_actors.push_back(std::make_shared<Game::Actor>(nullptr, glm::vec2(0.f, 0.f), window_size, 0.f));
		all_actors.push_back(std::make_shared<Game::Objects::Wall>(manager.GetTexture("textureAtlas"), manager.GetShaderProgram("spriteShader"), "wall", glm::vec2(800.f, 360.f), glm::vec2(240, 240)));
		all_actors.push_back(std::make_shared<Game::Objects::Wall>(manager.GetTexture("textureAtlas"), manager.GetShaderProgram("spriteShader"), "wall", glm::vec2(100.f, 600.f), glm::vec2(240, 240)));
		all_actors.push_back(std::make_shared<Game::Objects::Wall>(manager.GetTexture("textureAtlas"), manager.GetShaderProgram("spriteShader"), "wall", glm::vec2(800.f, 600.f), glm::vec2(240, 240)));

		std::vector<glm::vec2> patrolPos = {glm::vec2(100.f, 100.f),glm::vec2(150.f, 120.f),glm::vec2(120.f, 180.f) };

		auto pawn = std::make_shared<Game::MeleeEnemy>(manager.GetTexture("textureAtlas"), manager.GetShaderProgram("spriteShader"), "mush1", 20.f, patrolPos, glm::vec2(0.f), glm::vec2(100, 100));

		auto lastTime = std::chrono::high_resolution_clock::now();

		while (!glfwWindowShouldClose(window))
		{
			glClear(GL_COLOR_BUFFER_BIT);

			auto currentTime = std::chrono::high_resolution_clock::now();
			float duration = float(double(std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - lastTime).count()) / 1e9);
			lastTime = currentTime;

			main_character->Update(duration);
			for (std::shared_ptr<Game::Actor> actor : all_actors)
			{
				actor->Update(duration);
			}
			
			pawn->Update(duration);

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

	return 0;
}