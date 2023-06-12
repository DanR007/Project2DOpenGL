#pragma once

#include <memory>
#include <vector>
#include <iterator>

#include <glm/vec2.hpp>

#include "EngineManager.h"
#include "ResourcesManager.h"
#include "MemoryManager.h"

#include "../default_classes/Actor.h"

namespace Renderer
{
	class Texture2D;
	class ShaderProgram;
}

class NavMeshRTS;

class PlayerController;

class GameManager
{
public:
	GameManager();
	~GameManager();

	void Clear();
	

	template<typename T>
	std::shared_ptr<T> SpawnActor(const std::string& initSpriteName, const glm::vec2& actorPosition = glm::vec2(0.f),
		const glm::vec2& actorSize = glm::vec2(100.f, 100.f), const float actorRotation = 0.f)
	{
		std::shared_ptr<T> new_actor = std::make_shared<T>(initSpriteName, actorPosition, actorSize, actorRotation);

		int old_cap = _all_actors.capacity();

		if (std::dynamic_pointer_cast<Actor>(new_actor))
			_all_actors.emplace(_all_actors.end(), new_actor);

		GetEngine()->GetMemoryManager()->AddObject(std::dynamic_pointer_cast<Actor>(new_actor));

		return new_actor;
	}
	template<typename T>
	std::shared_ptr<T> SpawnActor(const glm::ivec2& position)
	{
		std::shared_ptr<T> new_actor = std::make_shared<T>(position);


		int old_cap = _all_actors.capacity();

		if (std::dynamic_pointer_cast<Actor>(new_actor))
			_all_actors.emplace(_all_actors.end(), new_actor);

		GetEngine()->GetMemoryManager()->AddObject(std::dynamic_pointer_cast<Actor>(new_actor));
		return new_actor;

	}

	void MoveAllActors(const glm::vec2& offset);

	void Update(const float& deltaTime);
	void BeginPlay();

	void SetGameOver(bool isGameOver) { _is_game_over = isGameOver; }

	void SetBlockSize(const glm::dvec2& size) { _block_size = size; }
	void SetOffset(const glm::dvec2& offset) { _offset = offset; }

	NavMeshRTS* GetNavMesh() const { return _nav_mesh; }

	void DeleteActor(std::vector<std::shared_ptr<Actor>>::iterator actor_iterator);

	glm::vec2 GetBlockSize() const { return _block_size; }
	//offset is map_coord - window_coord
	glm::vec2 GetOffset() const { return _offset; }
	glm::ivec2 GetSizeMap() const { return _size_map; }

	glm::vec2 ConvertToWindowSpace(const glm::ivec2& position_in_map);
	glm::vec2 ConvertToWindowSpace(const int& x, const int& y);
	glm::ivec2 ConvertToMapSpace(const glm::vec2& position_in_window);
	glm::ivec2 ConvertToMapSpace(const float& x, const float& y);

	PlayerController* GetPlayerController() { return _player_controller; }
	PlayerController* GetPlayerController(const unsigned short int& id) { return _controllers[id]; }

	std::vector<std::shared_ptr<Actor>> GetActors() { return _all_actors; }
	std::vector<std::shared_ptr<Actor>>& GetRefActors() { return _all_actors; }
	std::vector<Actor*> GetActorsOfType();

	void ReadMap();

	void Erase(std::shared_ptr<Actor> actor);
private:
	NavMeshRTS* _nav_mesh;
	PlayerController* _player_controller = nullptr;

	std::vector<std::shared_ptr<Actor>> _all_actors;

	std::vector<PlayerController*> _controllers;
	//offset is map_coord (multiply by block_size) - window_coord
	glm::vec2 _block_size, _offset;
	glm::ivec2 _start_point_map, _size_map;

	bool _is_game_over;

	friend class Physics::PhysicsManager;
};