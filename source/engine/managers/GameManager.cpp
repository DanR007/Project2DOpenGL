#include "GameManager.h"

#include "../../game/MainCharacter.h"
#include "../../game/enemies/MeleeEnemy.h"

#include "../controllers/PlayerController.h"
#include "../controllers/EnemyController.h"

#include "../../game/gameobjects/WallActor.h"
#include "../../game/gameobjects/HealActor.h"

#include "BSPMapGenerate.h"

#include <iostream>

void GameManager::MoveAllActors()
{
	auto it = _all_actors.begin();

	for (; it != _all_actors.end(); it++)
	{
		if (_main_character != *it)
		{
			it->get()->AddWorldPosition(_main_character->GetPlayerController()->GetMoveValue() * -1.f);

			if (std::dynamic_pointer_cast<Game::Enemy>(*it))
				std::dynamic_pointer_cast<Game::Enemy>(*it)->GetEnemyController()->ChangePatrolPointsCoordinate(_main_character->GetPlayerController()->GetMoveValue() * -1.f);
		}
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

	_main_character = nullptr;

	std::vector<std::string> map;
	MapGenerator* generator = new MapGenerator();
	int max = 25;
	map = generator->StartGenerate(glm::ivec2(max));

	glm::ivec2 player_position_generator = generator->GetCharacterPosition();
	glm::vec2 mainCharacterSize = glm::ivec2(35, 35);
	glm::vec2 position_player = glm::vec2((window_size.x - mainCharacterSize.x) / 2, (window_size.y - mainCharacterSize.y) / 2),
		block_size = glm::vec2(mainCharacterSize.x + 10.f, mainCharacterSize.y + 20.f), 
		offset = position_player;
	
	generator->Destroy();
	generator = nullptr;

	

	for (int i = 0; i < max + 2; i++)
	{
		for (int j = 0; j < max + 2; j++)
		{
			if (map[i][j] == 'B')
				SpawnActor<Game::Objects::Wall>("wall", glm::vec2( -(player_position_generator.x - j) * block_size.x + offset.x, (player_position_generator.y - i) * block_size.y + offset.y), block_size);
		}
	}

	std::vector<glm::vec2> patrolPos = { glm::vec2(300.f, 300.f),glm::vec2(0.f, 120.f),glm::vec2(300.f, 300.f) };

	std::shared_ptr<Game::MeleeEnemy> enemy = SpawnActor<Game::MeleeEnemy>("mush1", glm::vec2(0.f), glm::vec2(100, 100));
	enemy->GetEnemyController()->SetPatrolPoints(patrolPos);

	enemy->GetEnemyController()->SetMoveSpeed(50.f);

	//SpawnActor<Game::HealActor>("heal", glm::vec2(200.f, 200.f), glm::vec2(50.f, 50.f));

	std::vector<std::pair<std::string, float>> stateDuration =
	{
		std::make_pair(std::string("mush1"), 1.f),
		std::make_pair(std::string("mush2"), 1.f),
		std::make_pair(std::string("mush3"), 1.f)
	};

	_main_character = SpawnActor<Game::MainCharacter>("mush1",
		position_player, mainCharacterSize);
	_main_character->GetPlayerController()->SetMoveSpeed(300.f);

	_main_character->AddAnimState("walk", stateDuration);
	_main_character->PlayAnim("walk");
	_main_character->BeginPlay();
}

void GameManager::DeleteActor(std::vector<std::shared_ptr<Game::Actor>>::iterator delete_iterator)
{
	_all_actors.erase(delete_iterator);
}