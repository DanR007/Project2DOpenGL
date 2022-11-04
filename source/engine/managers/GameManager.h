#pragma once

#include <memory>
#include <vector>
#include <iterator>

#include <glm/vec2.hpp>

#include "ResourcesManager.h"
#include "PhysicsManager.h"

#include "../../game/MainCharacter.h"

#include "../default_classes/Actor.h"

namespace Renderer
{
	class Texture2D;
	class ShaderProgram;
}

class GameManager
{
public:
	GameManager() { _physics_manager = new PhysicsManager(this); }
	~GameManager() { if (_physics_manager) delete _physics_manager; }

	template<typename T>
	std::shared_ptr<T> SpawnActor(const std::string& initSpriteName, const glm::vec2& actorPosition = glm::vec2(0.f), const glm::vec2& actorSize = glm::vec2(100.f, 100.f), const float actorRotation = 0.f,
		std::shared_ptr<Renderer::Texture2D> texture = ResourcesManager::GetTexture("textureAtlas"),
		std::shared_ptr<Renderer::ShaderProgram> shader = ResourcesManager::GetShaderProgram("spriteShader"))
	{
		std::shared_ptr<T> new_actor = std::make_shared<T>(texture, shader, initSpriteName, actorPosition, actorSize, actorRotation); 

		if(std::dynamic_pointer_cast<Game::Actor>(new_actor))
			std::dynamic_pointer_cast<Game::Actor>(new_actor)->SetIterator(_all_actors.emplace(_all_actors.end(), new_actor));

		return new_actor;
	}

	void MoveAllActors();

	void Update(const float deltaTime);
	void BeginPlay();

	void SetGameOver(bool isGameOver) { _is_game_over = isGameOver; }
	void SetIterator(std::vector<std::shared_ptr<Game::Actor>>::iterator it) { _it = it; }

	PhysicsManager* GetPhysicsManager() { return _physics_manager; }

	void DeleteActor(std::vector<std::shared_ptr<Game::Actor>>::iterator delete_iterator);
private:
	PhysicsManager* _physics_manager;
	std::vector<std::shared_ptr<Game::Actor>>::iterator _it;

	std::vector<std::shared_ptr<Game::Actor>> _all_actors;
	std::shared_ptr<Game::MainCharacter> _main_character;

	bool _is_game_over;

	friend class PhysicsManager;
	friend class AStar;

	friend void glfwKeyCallback(GLFWwindow* currentWindow, int key, int scancode, int action, int mode);
	friend void glfwMouseButtonCallback(GLFWwindow* currentWindow, int button, int action, int mode);
};

