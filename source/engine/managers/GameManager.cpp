#include "GameManager.h"

#include "../../game/MainCharacter.h"
#include "../../game/enemies/MeleeEnemy.h"

#include "../physics/Collider.h"

#include "../../game/gameobjects/WallActor.h"
#include "../../game/gameobjects/HealActor.h"

#include "../controllers/PlayerController.h"
#include "../controllers/EnemyController.h"

#include "BSPMapGenerate.h"

#include <iostream>


void GameManager::MoveAllActors()
{
	auto it = _all_actors.begin();
	glm::vec2 offset = _main_character->GetPlayerController()->GetMoveValue() * -1.f;
	for (; it != _all_actors.end(); it++)
	{
		if (_main_character != *it)
		{
			it->get()->AddWorldPosition(offset);

			if (std::dynamic_pointer_cast<Game::Enemy>(*it))
				std::dynamic_pointer_cast<Game::Enemy>(*it)->GetEnemyController()->ChangePatrolPointsCoordinate(_main_character->GetPlayerController()->GetMoveValue() * -1.f);
		}
	}

	_nav_mesh->ChangeNavMeshCoord(offset);
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
				_physics_manager->CheckOverlapping(it->get()->GetCollider());

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
	_offset = position_player;
	//set offset as a player_start_position
	CreateMap();
	InitiateMainCharacter(main_character_size, position_player);

	std::vector<glm::vec2> patrolPos = { glm::vec2(300.f, 300.f),glm::vec2(0.f, 120.f),glm::vec2(300.f, 300.f) };

	std::shared_ptr<Game::MeleeEnemy> enemy = SpawnActor<Game::MeleeEnemy>("mush1", glm::vec2(0.f), glm::vec2(100, 100));
	enemy->GetEnemyController()->SetPatrolPoints(patrolPos);

	enemy->GetEnemyController()->SetMoveSpeed(50.f);

	//SpawnActor<Game::HealActor>("heal", glm::vec2(200.f, 200.f), glm::vec2(50.f, 50.f));
}

void GameManager::DeleteActor(std::vector<std::shared_ptr<Game::Actor>>::iterator actor_iterator)
{
	_all_actors.erase(actor_iterator);
}

void GameManager::CreateMap()
{
	std::vector<std::string> map;
	MapGenerator* generator = new MapGenerator();

	int max = 55;
	map = generator->StartGenerate(glm::ivec2(max));

	glm::ivec2 player_position_generator = generator->GetCharacterPosition();
	//generator->CreateNavMeshInRooms();

	generator->Destroy();
	generator = nullptr;

	for (int i = 0; i < max + 2; i++)
	{
		for (int j = 0; j < max + 2; j++)
		{
			if (map[i][j] == 'B')
			{
				std::pair<glm::vec2, glm::ivec2> s_c = WallCreater::GetWallSizeAndCoord(map, glm::ivec2(i, j), _block_size);
				glm::vec2 coordinate = glm::vec2(-(player_position_generator.x - s_c.second.y) * _block_size.x + _offset.x,
					(player_position_generator.y - s_c.second.x) * _block_size.y + _offset.y);
				SpawnActor<Game::Objects::Wall>("wall", coordinate, s_c.first);
			}
		}
	}
	int a = 0;
	//_nav_mesh->CreateNavMesh(map, _block_size, _block_size);
}

void GameManager::InitiateMainCharacter(const glm::vec2& main_character_size, const glm::vec2& position_player)
{
	std::vector<std::pair<std::string, float>> stateDuration =
	{
		std::make_pair(std::string("mush1"), 1.f),
		std::make_pair(std::string("mush2"), 1.f),
		std::make_pair(std::string("mush3"), 1.f)
	};

	_main_character = SpawnActor<Game::MainCharacter>("mush1",
		position_player, main_character_size);
	_main_character->GetPlayerController()->SetMoveSpeed(300.f);

	_main_character->AddAnimState("walk", stateDuration);
	_main_character->PlayAnim("walk");
	_main_character->BeginPlay();
}
