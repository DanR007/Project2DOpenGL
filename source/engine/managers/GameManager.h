#pragma once

#include <memory>
#include <vector>
#include <iterator>

#include <glm/vec2.hpp>

#include "EngineManager.h"
#include "ResourcesManager.h"
#include "MemoryManager.h"

#include "../default_classes/Actor.h"

#include "../generators/RTSMapGenerator.h"
#include "../../game/gameobjects/Resource.h"

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
	T* SpawnActor(const std::string& initSpriteName, const glm::vec2& actorPosition = glm::vec2(0.f),
		const glm::vec2& actorSize = glm::vec2(100.f, 100.f), const float actorRotation = 0.f)
	{
		T* new_actor = new T(initSpriteName, actorPosition, actorSize, actorRotation);

		if (dynamic_cast<Actor*>(new_actor))
			_all_actors.emplace(_all_actors.end(), new_actor);

		return new_actor;
	}
	template<typename T>
	T* SpawnActor(const glm::ivec2& position)
	{
		T* new_actor = new T(position);

		if (dynamic_cast<Actor*>(new_actor))
			_all_actors.emplace(_all_actors.end(), new_actor);

		return new_actor;

	}

	template<typename T>
	void FillCell(Cell* cell, const EResourceTypes& type)
	{
		SpawnActor<T>(cell->_position);
		cell->_resource = dynamic_cast<T*>(_all_actors.back());
		cell->_resource->SetCell(cell);
		cell->_resource->SetResource(type);
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
	std::vector<std::vector<Cell*>> GetMap() const { return _map; }

	glm::vec2 ConvertToWindowSpace(const glm::ivec2& position_in_map);
	glm::vec2 ConvertToWindowSpace(const int& x, const int& y);
	glm::ivec2 ConvertToMapSpace(const glm::vec2& position_in_window);
	glm::ivec2 ConvertToMapSpace(const float& x, const float& y);

	PlayerController* GetFirstPlayerController() { return _player_controller; }
	PlayerController* GetPlayerController(const unsigned short int& id) { return _controllers[id]; }

	std::vector<Actor*> GetActors() { return _all_actors; }
	std::vector<Actor*> GetActorsOfType();

	void ReadMap();

	void Erase(Actor* actor);
private:
	NavMeshRTS* _nav_mesh;
	PlayerController* _player_controller = nullptr;

	std::vector<Actor*> _all_actors;

	std::vector<std::vector<Cell*>> _map;

	std::vector<PlayerController*> _controllers;
	//offset is map_coord (multiply by block_size) - window_coord
	glm::vec2 _block_size, _offset;
	glm::ivec2 _start_point_map, _size_map;

	bool _is_game_over;

	friend class Physics::PhysicsManager;
};
