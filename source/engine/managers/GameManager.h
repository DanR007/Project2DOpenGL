#pragma once

#include <memory>
#include <vector>
#include <iterator>

#include <glm/vec2.hpp>

#include "ResourcesManager.h"
#include "PhysicsManager.h"

#include "../AI/NavMesh.h"

#include "../default_classes/Actor.h"

namespace Renderer
{
	class Texture2D;
	class ShaderProgram;
}

class PlayerController;

class GameManager
{
public:
	GameManager() 
	{ 
		_physics_manager = new Physics::PhysicsManager(this); 
		_nav_mesh = new NavMeshRTS();

		_size_map = glm::ivec2(7);
	}
	~GameManager() 
	{
		if (_physics_manager) 
		{
			delete _physics_manager; 
			_physics_manager = nullptr;
		}
		if (_nav_mesh)
		{
			delete _nav_mesh;
			_nav_mesh = nullptr;
		}
	}

	void Clear();
	

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
	void SetBlockSize(const glm::dvec2& size) { _block_size = size; }
	void SetOffset(const glm::dvec2& offset) { _offset = offset; }

	Physics::PhysicsManager* GetPhysicsManager() const { return _physics_manager; }
	NavMeshRTS* GetNavMesh() const { return _nav_mesh; }

	void DeleteActor(std::vector<std::shared_ptr<Game::Actor>>::iterator actor_iterator);

	glm::vec2 GetBlockSize() const { return _block_size; }
	//offset is map_coord - window_coord
	glm::vec2 GetOffset() const { return _offset; }
	glm::ivec2 GetSizeMap() const { return _size_map; }

	std::vector<std::shared_ptr<Game::Actor>> GetActors() { return _all_actors; }
	std::vector<std::shared_ptr<Game::Actor>> GetActorsOfType();

	void ReadMap(std::vector<std::string>& map, const glm::ivec2& middle_position);
private:
	void InitiateMainCharacter(const glm::vec2& main_character_size, const glm::vec2& position_player);
	

	Physics::PhysicsManager* _physics_manager;
	NavMeshRTS* _nav_mesh;
	PlayerController* _player_controller = nullptr;

	std::vector<std::shared_ptr<Game::Actor>>::iterator _it;

	std::vector<std::shared_ptr<Game::Actor>> _all_actors;

	//offset is map_coord (multiply by block_size) - window_coord
	glm::vec2 _block_size, _offset;
	glm::ivec2 _start_point_map, _size_map;

	bool _is_game_over;

	friend class Physics::PhysicsManager;
	
	friend void glfwKeyCallback(GLFWwindow* currentWindow, int key, int scancode, int action, int mode);
	friend void glfwMouseButtonCallback(GLFWwindow* currentWindow, int button, int action, int mode);
};

