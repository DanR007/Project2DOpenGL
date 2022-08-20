#include "GameManager.h"
#include "ResourcesManager.h"

#include "../../game/MainCharacter.h"
#include "../../game/enemies/MeleeEnemy.h"

#include "../../game/enemies/MeleeEnemy.h"

#include "../../game/gameobjects/WallActor.h"

std::vector<std::shared_ptr<Game::Actor>> all_actors;
std::vector<std::shared_ptr<Game::Pawn>> all_pawns;
std::shared_ptr<Game::MainCharacter> main_character;

void GameManager::MoveAllActors(const glm::vec2& valuePosition)
{
	for (std::shared_ptr<Game::Actor> actor : all_actors)
	{
		actor->SetPosition(actor->GetPosition() - valuePosition);

		if(std::dynamic_pointer_cast<Game::MeleeEnemy>(actor))
			std::dynamic_pointer_cast<Game::MeleeEnemy>(actor)->ChangePatrolPointsCoordinate(main_character->GetMoveVector() * -1.f);
	}
}

void GameManager::Update(const float deltaTime)
{
	main_character->Update(deltaTime);
	size_t size = all_actors.size();
	/*for (size_t i = 0; i < size; i++)
	{
		if (std::dynamic_pointer_cast<Game::MeleeEnemy>(std::dynamic_pointer_cast<Game::Pawn>(all_actors[i])))
			std::dynamic_pointer_cast<Game::MeleeEnemy>(std::dynamic_pointer_cast<Game::Pawn>(all_actors[i]))->Update(deltaTime);
		else
			all_actors[i]->Update(deltaTime);
	}*/

	for (std::shared_ptr<Game::Actor> actor : all_actors)
	{
		if (std::dynamic_pointer_cast<Game::MeleeEnemy>(actor))
			std::dynamic_pointer_cast<Game::MeleeEnemy>(actor)->Update(deltaTime);
		else
			actor->Update(deltaTime);
	}
}

void GameManager::BeginPlay()
{
	glm::vec2 mainCharacterSize = glm::ivec2(100, 100);
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

	SpawnActor<Game::Objects::Wall>("wall", glm::vec2(800.f, 360.f), glm::vec2(240, 240));
	SpawnActor<Game::Objects::Wall>("wall", glm::vec2(100.f, 600.f), glm::vec2(240, 240));
	SpawnActor<Game::Objects::Wall>("wall", glm::vec2(800.f, 600.f), glm::vec2(240, 240));
	std::vector<glm::vec2> patrolPos = { glm::vec2(100.f, 100.f),glm::vec2(150.f, 120.f),glm::vec2(120.f, 180.f) };

	std::shared_ptr<Game::MeleeEnemy> enemy = SpawnActor<Game::MeleeEnemy>("mush1", glm::vec2(0.f), glm::vec2(100, 100));
	enemy->SetPatrolPoints(patrolPos);

	enemy->SetMoveSpeed(50.f);
}
