#include "main.h"

#include "engine/managers/ResourcesManager.h"
#include "engine/managers/PhysicsManager.h"
#include "engine/managers/GameManager.h"

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
#include <thread>

std::vector<Game::Pawn*> pawns;
std::shared_ptr<Game::MainCharacter> main_character;
std::vector<std::shared_ptr<Game::Actor>> GameManager::all_actors;
std::vector<std::shared_ptr<Game::Pawn>> all_pawns;

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
		ResourcesManager::ResourcesManager(*argv);

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
		auto textureShader = ResourcesManager::LoadShaderPrograms("texture", TEXTURE_FRAGMENT_SHADER_PATH, TEXTURE_VERTEX_SHADER_PATH);
		auto spriteShader = ResourcesManager::LoadShaderPrograms("spriteShader", SPRITE_FRAGMENT_SHADER_PATH, SPRITE_VERTEX_SHADER_PATH);

		glClearColor(1.f, 1.f, 1.f, 1.f);

		std::vector<std::string> names = { "mush1", "mush2", "mush3", "wall"};
		
		ResourcesManager::LoadTextureAtlas("textureAtlas", "resources/textures/mushroom.png", names, 16, 16);
		//textureAtlas - texture name
		//names - vector of names subtextures

		glm::vec2 mainCharacterSize = glm::ivec2(100, 100);
		main_character = GameManager::SpawnActor<Game::MainCharacter>("mush1",
			glm::vec2(window_size.x / 2 - mainCharacterSize.x / 2, window_size.y / 2 - mainCharacterSize.y / 2), mainCharacterSize);

		glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(window_size.x), 0.f, static_cast<float>(window_size.y), -100.f, 100.f);
		ResourcesManager::GetShaderProgram("spriteShader")->Use();
		ResourcesManager::GetShaderProgram("spriteShader")->SetIn("tex", 0);
		ResourcesManager::GetShaderProgram("spriteShader")->SetMatrix4("projectionMat", projectionMatrix);

		std::vector<std::pair<std::string, float>> stateDuration =
		{
			std::make_pair(std::string("mush1"), 1.f),
			std::make_pair(std::string("mush2"), 1.f),
			std::make_pair(std::string("mush3"), 1.f)
		};

		main_character->AddAnimState("walk", stateDuration);
		main_character->PlayAnim("walk");
		main_character->BeginPlay();

		main_character->SetMoveSpeed(100.f);
		//all_actors.push_back(std::make_shared<Game::Actor>(nullptr, glm::vec2(0.f, 0.f), window_size, 0.f));
		//all_actors.push_back(GameManager::SpawnActor<Game::Objects::Wall>("wall", glm::vec2(800.f, 360.f), glm::vec2(240, 240)));
		//all_actors.push_back(std::make_shared<Game::Objects::Wall>(ResourcesManager::GetTexture("textureAtlas"), ResourcesManager::GetShaderProgram("spriteShader"), "wall", glm::vec2(100.f, 600.f), glm::vec2(240, 240)));
		//all_actors.push_back(std::make_shared<Game::Objects::Wall>(ResourcesManager::GetTexture("textureAtlas"), ResourcesManager::GetShaderProgram("spriteShader"), "wall", glm::vec2(800.f, 600.f), glm::vec2(240, 240)));
		//all_actors.push_back(GameManager::SpawnActor<Game::Objects::Wall>("wall", glm::vec2(100.f, 600.f), glm::vec2(240, 240), 0.f));
		//all_actors.push_back(GameManager::SpawnActor<Game::Objects::Wall>("wall", glm::vec2(800.f, 600.f), glm::vec2(240, 240), 0.f));
		GameManager::SpawnActor<Game::Objects::Wall>("wall", glm::vec2(800.f, 600.f), glm::vec2(240, 240), 0.f);
		std::vector<glm::vec2> patrolPos = {glm::vec2(100.f, 100.f),glm::vec2(150.f, 120.f),glm::vec2(120.f, 180.f) };

		//all_pawns.push_back(std::make_shared<Game::MeleeEnemy>(ResourcesManager::GetTexture("textureAtlas"), ResourcesManager::GetShaderProgram("spriteShader"), "mush1", 20.f, patrolPos, glm::vec2(0.f), glm::vec2(100, 100)));

		auto lastTime = std::chrono::high_resolution_clock::now();

		while (!glfwWindowShouldClose(window))
		{
			glClear(GL_COLOR_BUFFER_BIT);

			auto currentTime = std::chrono::high_resolution_clock::now();
			float duration = float(double(std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - lastTime).count()) / 1e9);
			lastTime = currentTime;

			main_character->Update(duration);

			GameManager::Update(duration);

			for (std::shared_ptr<Game::Pawn> pawn : all_pawns)
			{
				pawn->Update(duration);
			}
			

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

	return 0;
}