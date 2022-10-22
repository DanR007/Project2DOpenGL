#include "GameManager.h"

#include "../../game/MainCharacter.h"
#include "../../game/enemies/MeleeEnemy.h"

#include "../controllers/PlayerController.h"
#include "../controllers/EnemyController.h"

#include "../../game/gameobjects/WallActor.h"
#include "../../game/gameobjects/HealActor.h"

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
		//main_character->Update(deltaTime);
		
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

	SpawnActor<Game::Objects::Wall>("wall", glm::vec2(800.f, 360.f), glm::vec2(240, 240));
	SpawnActor<Game::Objects::Wall>("wall", glm::vec2(100.f, 600.f), glm::vec2(240, 240));
	SpawnActor<Game::Objects::Wall>("wall", glm::vec2(800.f, 600.f), glm::vec2(240, 240));
	SpawnActor<Game::Objects::Wall>("wall", glm::vec2(120.f, 120.f), glm::vec2(100, 100));
	std::vector<glm::vec2> patrolPos = { glm::vec2(300.f, 300.f),glm::vec2(0.f, 120.f),glm::vec2(300.f, 300.f) };

	std::shared_ptr<Game::MeleeEnemy> enemy = SpawnActor<Game::MeleeEnemy>("mush1", glm::vec2(0.f), glm::vec2(100, 100));
	enemy->GetEnemyController()->SetPatrolPoints(patrolPos);

	enemy->GetEnemyController()->SetMoveSpeed(50.f);

	//SpawnActor<Game::HealActor>("heal", glm::vec2(200.f, 200.f), glm::vec2(50.f, 50.f));

	glm::vec2 mainCharacterSize = glm::ivec2(50, 50);
	main_character = SpawnActor<Game::MainCharacter>("mush1",
		glm::vec2(window_size.x / 2 - mainCharacterSize.x / 2, window_size.y / 2 - mainCharacterSize.y / 2), mainCharacterSize);


	std::vector<std::pair<std::string, float>> stateDuration =
	{
		std::make_pair(std::string("mush1"), 1.f),
		std::make_pair(std::string("mush2"), 1.f),
		std::make_pair(std::string("mush3"), 1.f)
	};

	main_character->AddAnimState("walk", stateDuration);
	main_character->PlayAnim("walk");
	main_character->BeginPlay();

	main_character->SetMoveSpeed(100.f);
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