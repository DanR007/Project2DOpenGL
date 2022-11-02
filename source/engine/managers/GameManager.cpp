#include "GameManager.h"

#include "../../game/MainCharacter.h"
#include "../../game/enemies/MeleeEnemy.h"

#include "../controllers/PlayerController.h"
#include "../controllers/EnemyController.h"

#include "../../game/gameobjects/WallActor.h"
#include "../../game/gameobjects/HealActor.h"

#include "BSPMapGenerate.h"

#include <iostream>

std::vector<std::shared_ptr<Game::Actor>> all_actors;
std::vector<std::shared_ptr<Game::Pawn>> all_pawns;
std::shared_ptr<Game::MainCharacter> main_character;

bool GameManager::_is_game_over;
std::vector<std::shared_ptr<Game::Actor>>::iterator GameManager::_it;

std::vector<std::shared_ptr<Game::Actor>> GameManager::_all_actors;

void GameManager::MoveAllActors()
{
	auto it = _all_actors.begin();

	for (; it != _all_actors.end(); it++)
	{
		if (main_character != *it)
		{
			it->get()->AddWorldPosition(main_character->GetPlayerController()->GetMoveValue() * -1.f);

			if (std::dynamic_pointer_cast<Game::MeleeEnemy>(*it))
				std::dynamic_pointer_cast<Game::MeleeEnemy>(*it)->ChangePatrolPointsCoordinate(main_character->GetMoveValue() * -1.f);
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

	main_character = nullptr;

	std::vector<std::string> map;
	MapGenerator* generator = new MapGenerator();
	int max = 25;
	map = generator->StartGenerate(glm::ivec2(max));

	glm::ivec2 player_position = generator->GetCharacterPosition();
	glm::vec2 mainCharacterSize = glm::ivec2(35, 35);
	glm::vec2 position = glm::vec2(window_size.x / 2 - mainCharacterSize.x / 2, window_size.y / 2 - mainCharacterSize.y / 2),
		offset = -glm::vec2(player_position * 40) + position;

	generator->Destroy();
	generator = nullptr;

	main_character = SpawnActor<Game::MainCharacter>("mush1",
		glm::vec2(player_position * 40), mainCharacterSize);
	main_character->GetPlayerController()->SetMoveSpeed(300.f);

	for (int i = 0; i < max + 2; i++)
	{
		for (int j = 0; j < max + 2; j++)
		{
			if (map[i][j] == 'B')
				SpawnActor<Game::Objects::Wall>("wall", glm::vec2(j * 40.f, i * 40.f), glm::vec2(40.f, 40.f));
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

	main_character->AddAnimState("walk", stateDuration);
	main_character->PlayAnim("walk");
	main_character->BeginPlay();


}

void GameManager::DeleteActor(Game::Actor* actor)
{
	auto it = _all_actors.begin();
	for (; it != _all_actors.end(); it++)
	{
		if (it->get() == actor)
		{
			_all_actors.erase(it);
			break;
		}
	}
}