#include "GameManager.h"
#include "EngineManager.h"
#include "HUDManager.h"
#include "RenderManager.h"

#include "../physics/Collider.h"

#include "../controllers/PlayerController.h"

#include "../AI/AStarRTS.h"

#include "../AI/NavMesh.h"

#include "../../game/gameobjects/units/Unit.h"

#include "../../game/gameobjects/static/resources/Stone.h"
#include "../../game/gameobjects/static/resources/Wood.h"
#include "../../game/gameobjects/static/Water.h"
#include "../../game/gameobjects/static/Ground.h"

#include "../UI/Widget.h"
#include "../UI/Text.h"
#include "../UI/Panel.h"

#include "../renderer/AnimSprite.h"

#include <numeric>
#include <thread>

#ifdef __linux__
#include <algorithm>
#endif //__linux__

GameManager::GameManager()
{
	_nav_mesh = new NavMeshRTS();

	_size_map = glm::ivec2(10);
}

GameManager::~GameManager()
{
	Clear();
	if (_nav_mesh)
	{
		delete _nav_mesh;
		_nav_mesh = nullptr;
	}

	if (_player_controller)
	{
		delete _player_controller;
		_player_controller = nullptr;
	}
}

void GameManager::Clear()
{
	for (Actor* a : _all_actors)
	{
		a->Destroy();
		a = nullptr;
	}
	_all_actors.clear();

	for (size_t y = 0; y < _map.size(); y++)
	{
		for (size_t x = 0; x < _map[y].size(); x++)
		{
			delete _map[y][x];
		}
		_map[y].clear();
	}
	_map.clear();
}


void GameManager::MoveAllActors(const glm::vec2& offset)
{
#ifndef MULTITHREADING
	auto it = _all_actors.begin();
	_offset -= offset;
	for (; it != _all_actors.end(); ++it)
	{
		Unit* u = dynamic_cast<Unit*>(*it);

		if (u)
		{
			if(u->GetController())
			{
				u->GetController()->ChangeNodePositionWindow(offset);
			}
			else
			{
#ifdef DEBUG_DESTRUCTOR
	std::cout << "Controller is nullptr in MoveAllActors" << std::endl;
#endif
			}
		}

		(*it)->SetPosition((*it)->GetPosition() + offset);
	}
#else
	std::thread t1 = std::thread(&GameManager::MoveAllActorsMultithreading, this, std::ref(offset), 0, _all_actors.size() / 2);
	std::thread t2 = std::thread(&GameManager::MoveAllActorsMultithreading, this, std::ref(offset), _all_actors.size() / 2, _all_actors.size());

	t1.join();
	t2.join();
#endif // MULTITHREADING
}

void GameManager::MoveAllActorsMultithreading(const glm::vec2& offset, size_t begin, size_t end)
{
	std::vector<Actor*>::const_iterator it = _all_actors.begin() + begin;
	std::vector<Actor*>::const_iterator it_end = _all_actors.begin() + end;
	_offset -= offset;
	for (; it != it_end; ++it)
	{
		Unit* u = dynamic_cast<Unit*>(*it);

		if (u)
		{
			if(u->GetController())
			{
				u->GetController()->ChangeNodePositionWindow(offset);
			}
			else
			{
#ifdef DEBUG_DESTRUCTOR
	std::cout << "Controller is nullptr in MoveAllActors" << std::endl;
#endif
			}
		}

		(*it)->SetPosition((*it)->GetPosition() + offset);
	}
}

void GameManager::Update(const float& deltaTime)
{

	if (!_is_game_over)
	{
		_player_controller->Move(deltaTime);

#ifndef MULTITHREADING
		std::vector<Actor*>::const_iterator it = _all_actors.begin();
		
		for (; it != _all_actors.end(); ++it)
		{
			(*it)->Update(deltaTime);
		}
#else
		std::thread t1 = std::thread(&GameManager::UpdateMultithreading, this, std::ref(deltaTime), 0, _all_actors.size() / 2);
		std::thread t2 = std::thread(&GameManager::UpdateMultithreading, this, std::ref(deltaTime), _all_actors.size() / 2, _all_actors.size());

		t1.join();
		t2.join();
#endif // MULTITHREADING
	}
	else
	{
		//here add game over menu
	}
	
}

void GameManager::UpdateMultithreading(const float& deltaTime, size_t begin, size_t end)
{
	std::vector<Actor*>::const_iterator it = _all_actors.begin() + begin;
	std::vector<Actor*>::const_iterator it_end = _all_actors.begin() + end;
	for (; it != it_end; ++it)
	{
		(*it)->Update(deltaTime);
	}
}

void GameManager::BeginPlay()
{
	SetGameOver(false);

	_block_size = glm::vec2(45.f);

	Widget* wdg = GetEngine()->GetHUDManager()->CreateWidget();

	_player_controller = new PlayerController(0, wdg);

	_controllers.push_back(_player_controller);

	RTSMapGenerator* generator = new RTSMapGenerator(_size_map);
	_map = generator->GenerateMap();
	ReadMap();

	_nav_mesh->FillMap(_map);

	delete generator;
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
			Cell* cell = _map[y][x];
			char symbol = cell->_symbol;
			switch (symbol)
			{
			case 'T':
				FillCell<Wood>(cell, EResourceTypes::ERT_Wood);
				break;
			case 'S':
				FillCell<Stone>(cell, EResourceTypes::ERT_Stone);
				break;
			}

			if(symbol == 'W')
			{
				SpawnActor<Water>(cell->_position);
			}
			else
			{
				SpawnActor<Ground>(cell->_position);
			}
		}
	}
}

void GameManager::Erase(Actor* actor)
{
	auto it = std::find(_all_actors.begin(), _all_actors.end(), actor);
	_all_actors.erase(it);
}

