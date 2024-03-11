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
#include "../../game/gameobjects/static/resources/Resource.h"

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
			_new_actors.emplace(_new_actors.end(), new_actor);

		return new_actor;
	}
	template<typename T>
	T* SpawnActor(const glm::ivec2& position)
	{
		T* new_actor = new T(position);

		if (dynamic_cast<Actor*>(new_actor))
			_new_actors.emplace(_new_actors.end(), new_actor);

		return new_actor;

	}

	/// @brief заполнение клетки и создание объекта, который находится в клетке
	/// @tparam T 
	/// @param cell клетка на карте
	/// @param type тип клетки
	template<typename T>
	void FillCell(Cell* cell, const EResourceTypes& type)
	{
		Actor* actor = SpawnActor<T>(cell->_position);
		cell->_actor = dynamic_cast<T*>(actor);
		Resource* res = dynamic_cast<Resource*>(cell->_actor);
		if(res)
		{
			res->SetCell(cell);
			res->SetResource(type);
		}
	}

	/// @brief перемещение всех Actor создавая ощущение перемещения камеры 
	/// @param offset смещение Actor
	void MoveAllActors(const glm::vec2& offset);
	/// @brief Вызывается каждый кадр
	/// @param deltaTime время с последнего таймера
	void Update(const float& deltaTime);
	void BeginPlay();

	void SetGameOver(bool isGameOver) { _is_game_over = isGameOver; }

	void SetBlockSize(const glm::dvec2& size) { _block_size = size; }
	void SetOffset(const glm::dvec2& offset) { _offset = offset; }

	NavMeshRTS* GetNavMesh() const { return _nav_mesh; }

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
	/// @brief отвечает за объединение новых объектов со старыми
	void MergeNewActors();


	/// @brief Update если включен в main.h многопоток
	/// @param deltaTime 
	/// @param begin начало обработки массива _all_actors в этом потоке
	/// @param end конец обработки массива в потоке
	void UpdateMultithreading(const float& deltaTime, size_t begin, size_t end);
	/// @brief MoveAllActors если включен в main.h многопоток
	/// @param offset 
	/// @param begin начало обработки массива _all_actors в этом потоке
	/// @param end конец обработки массива в потоке
	void MoveAllActorsMultithreading(const glm::vec2& offset, size_t begin, size_t end);
	
	/// @brief навигационная "сетка" отвечает за перемещение юнитов по карте
	NavMeshRTS* _nav_mesh;
	PlayerController* _player_controller = nullptr;

	/// @brief отвечает за только что созданные объекты
	std::vector<Actor*> _new_actors;

	std::vector<Actor*> _all_actors;
	/// @brief карта игры
	std::vector<std::vector<Cell*>> _map;
	/// @brief контроллеры игроков
	std::vector<PlayerController*> _controllers;
	/// @brief размер клетки на экране
	glm::vec2 _block_size;
	/// @brief offset is map_coord (multiply by block_size) - window_coord
	glm::vec2 _offset;
	glm::ivec2 _start_point_map;
	/// @brief размер карты
	glm::ivec2 _size_map;
	/// @brief переменная отвечающая за окончание игры
	bool _is_game_over;

	friend class Physics::PhysicsManager;
};
