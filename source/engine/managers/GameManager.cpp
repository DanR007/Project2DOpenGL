#include "GameManager.h"

void GameManager::MoveAllActors(const glm::vec2& valuePosition)
{
	for (std::shared_ptr<Game::Actor> actor : all_actors)
	{
		actor->SetPosition(actor->GetPosition() - valuePosition);
	}
}

void GameManager::Update(const float deltaTime)
{
	for (std::shared_ptr<Game::Actor> actor : all_actors)
	{
		actor->Update(deltaTime);
	}
}
