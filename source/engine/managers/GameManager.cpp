#include "GameManager.h"

#include "../physics/Collider.h"

#include "../controllers/PlayerController.h"

#include <iostream>

#include "../AI/AStarRTS.h"

#include "../AI/NavMesh.h"

#include "../../game/gameobjects/Unit.h"
#include "../../game/gameobjects/Wall.h"

#include "../../game/gameobjects/static/Stone.h"
#include "../../game/gameobjects/static/Wood.h"


GameManager::GameManager()
{
	_physics_manager = new Physics::PhysicsManager(this);
	_nav_mesh = new NavMeshRTS();

	_size_map = glm::ivec2(50);
}

GameManager::~GameManager()
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

void GameManager::Clear()
{
	_all_actors.clear();
}


void GameManager::MoveAllActors(const glm::vec2& offset)
{
	auto it = _all_actors.begin();
	_offset -= offset;
	for (; it != _all_actors.end(); it++)
	{
		std::shared_ptr<Unit> u = std::dynamic_pointer_cast<Unit>(*it);

		if (u)
		{
			u->Move(u->GetPosition() + offset);
			u->GetController()->ChangeGoalPositionWindow(offset);
		}
		else
		{
			it->get()->AddWorldPosition(offset);
		}
	}
}

void GameManager::Update(const float& deltaTime)
{
	if (_is_game_over == false)
	{
		_player_controller->Move(deltaTime);

		auto it = _all_actors.begin();
		
		for (; it != _all_actors.end(); it++)
		{
			if (it->get())
			{
				it->get()->Update(deltaTime);
			}
		}

		ClearDeleteActors();
	}
	else
	{
		//here add game over menu
	}
}

void GameManager::BeginPlay()
{
	SetGameOver(false);

	_block_size = glm::vec2(45.f);

	_player_controller = new PlayerController();

	_controllers.push_back(_player_controller);

	SpawnActor<Unit>("mush1", ConvertToWindowSpace(0, 0), _block_size);

	RTSMapGenerator* generator = new RTSMapGenerator(_size_map);
	_nav_mesh->FillMap(generator->GenerateMap());

	ReadMap();
	//star->DevelopPath(Cell(glm::ivec2(0), 0, 1, '.', 2), Cell(glm::ivec2(4, 0), 0, 1, '.', 1));
}

void GameManager::DeleteActor(std::vector<std::shared_ptr<Actor>>::iterator actor_iterator)
{
	_need_to_delete.push_back(actor_iterator);
	//clear map here
}

glm::vec2 GameManager::ConvertToWindowSpace(const glm::ivec2& position_in_map)
{
	return glm::vec2(position_in_map.x * _block_size.x, position_in_map.y * _block_size.y) - _offset;
}
glm::vec2 GameManager::ConvertToWindowSpace(const int& x, const int& y)
{
	return glm::vec2(x * _block_size.x, y * _block_size.y) - _offset;
}

glm::ivec2 GameManager::ConvertToMapSpace(const glm::vec2& position_in_window)
{
	glm::ivec2 map_coord;
	if ((position_in_window.x + _offset.x) < 0)
		map_coord = glm::ivec2(-1, 0);
	else
		map_coord = glm::ivec2((position_in_window.x + _offset.x) / _block_size.x, 0);

	if ((position_in_window.y + _offset.y) < 0)
		map_coord += glm::ivec2(0, -1);
	else
		map_coord += glm::ivec2(0, (position_in_window.y + _offset.y) / _block_size.y);

	return map_coord;
}
glm::ivec2 GameManager::ConvertToMapSpace(const float& x, const float& y)
{
	glm::ivec2 map_coord;
	if ((x + _offset.x) < 0)
		map_coord = glm::ivec2(-1, 0);
	else
		map_coord = glm::ivec2((x + _offset.x) / _block_size.x, 0);

	if ((y + _offset.y) < 0)
		map_coord += glm::ivec2(0, -1);
	else
		map_coord += glm::ivec2(0, (y + _offset.y) / _block_size.y);

	return map_coord;
}


void GameManager::ReadMap()
{
	for (int y = _size_map.y - 1; y >= 0; y--)
	{
		for (int x = 0; x < _size_map.x; x++)
		{

			char symbol = GetNavMesh()->GetMap()[y][x]._symbol;
			switch (symbol)
			{
			case 'W':
				SpawnActor<Wood>(glm::ivec2(x, y));
				break;
			case 'S':
				SpawnActor<Stone>(glm::ivec2(x, y));
				break;
			case 'B':
				SpawnActor<Wall>("wall", ConvertToWindowSpace(x, y), _block_size);
				break;
			}

		}
	}
}

void GameManager::ChangeIterators()
{
	_need_to_delete.clear();

	auto it = _all_actors.begin();

	for (; it != _all_actors.end(); it++)
	{
		if ((*it)->GetDeleteFlag())
			_need_to_delete.push_back(it);

		(*it)->SetIterator(it);
	}
}

void GameManager::ClearDeleteActors()
{
	if (_need_to_delete.empty() == false)
	{
		auto it = _all_actors.begin();
		for (; it != _all_actors.end();)
		{
			if ((*it)->GetDeleteFlag())
				it = _all_actors.erase(it);
			else
				it++;
		}

		_need_to_delete.clear();
	}
}
