#include "GameManager.h"

#include "../physics/Collider.h"

#include "../controllers/PlayerController.h"

#include <iostream>

#include "../AI/AStarRTS.h"

#include "../../game/gameobjects/Unit.h"

void GameManager::Clear()
{
	_all_actors.clear();
}


void GameManager::MoveAllActors()
{
	auto it = _all_actors.begin();
	glm::vec2 offset = glm::vec2(0.f);
	for (; it != _all_actors.end(); it++)
	{
		it->get()->AddWorldPosition(offset);
	}
}

void GameManager::Update(const float deltaTime)
{
	if (_is_game_over == false)
	{
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

	_offset = glm::vec2(_size_map.x / 2 * _block_size.x, _size_map.y / 2 * _block_size.y) - glm::vec2(window_size / 2);

	SpawnActor<Unit>("mush1", glm::vec2(0) - _offset, glm::vec2(45.f));

	_player_controller = new PlayerController();

	RTSMapGenerator* generator = new RTSMapGenerator(glm::ivec2(0));
	_nav_mesh->FillMap(generator->GenerateMap());

	//star->DevelopPath(Cell(glm::ivec2(0), 0, 1, '.', 2), Cell(glm::ivec2(4, 0), 0, 1, '.', 1));
}

void GameManager::DeleteActor(std::vector<std::shared_ptr<Game::Actor>>::iterator actor_iterator)
{
	bool is_blocking_actor = actor_iterator->get()->GetCollider()->GetResponseType(EObjectTypes::EOT_Pawn) == EResponseType::ERT_Block;
	
	_all_actors.erase(actor_iterator);

	//clear map here
}

void GameManager::ReadMap(std::vector<std::string>& map, const glm::ivec2& middle_position)
{
	for (int y = map.size() - 1; y >= 0; y--)
	{
		for (int x = 0; x < map.size(); x++)
		{
			
		}
	}
}
