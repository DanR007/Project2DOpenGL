#include "GameManager.h"

#include "../physics/Collider.h"

#include "../controllers/PlayerController.h"

#include <iostream>

#include "../AI/AStarRTS.h"

#include "../../game/gameobjects/Unit.h"
#include "../../game/gameobjects/Wall.h"

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
		it->get()->AddWorldPosition(offset);

		if (std::dynamic_pointer_cast<Unit>(*it))
			std::dynamic_pointer_cast<Unit>(*it)->GetController()->ChangeGoalPositionWindow(offset);
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

				if (it == _all_actors.end())
					break;
			}
		}
	}
	else
	{
		//here add game over menu
	}
}

void GameManager::BeginPlay()
{
	SetGameOver(false);

	glm::vec2 main_character_size = glm::ivec2(35, 35);
	glm::vec2 position_player = glm::vec2((window_size.x - main_character_size.x) / 2, (window_size.y - main_character_size.y) / 2);

	_block_size = main_character_size + glm::vec2(10.f);

	_player_controller = new PlayerController();

	_controllers.push_back(_player_controller);

	SpawnActor<Unit>("mush1", glm::vec2(0) - _offset, _block_size);

	RTSMapGenerator* generator = new RTSMapGenerator(glm::ivec2(0));
	_nav_mesh->FillMap(generator->GenerateMap());

	ReadMap();
	//star->DevelopPath(Cell(glm::ivec2(0), 0, 1, '.', 2), Cell(glm::ivec2(4, 0), 0, 1, '.', 1));
}

void GameManager::DeleteActor(std::vector<std::shared_ptr<Game::Actor>>::iterator actor_iterator)
{
	bool is_blocking_actor = actor_iterator->get()->GetCollider()->GetResponseType(EObjectTypes::EOT_Pawn) == EResponseType::ERT_Block;
	
	_all_actors.erase(actor_iterator);

	//clear map here
}

void GameManager::ReadMap()
{
	for (int y = _size_map.y - 1; y >= 0; y--)
	{
		for (int x = 0; x < _size_map.x; x++)
		{
			if (GetNavMesh()->GetMap()[y][x]._cost == -1)
			{
				SpawnActor<Wall>("wall", glm::vec2(x * _block_size.x, y * _block_size.y) - _offset, _block_size);
			}
		}
	}
}
