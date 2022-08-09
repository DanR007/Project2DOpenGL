#include "PhysicsManager.h"
#include "../../game/Actor.h"


bool PhysicsManager::CanMove(std::vector<std::shared_ptr<Game::Actor>>& actorNeedToCheck, const glm::vec2& nextPosition, const glm::vec2& sizeActor)
{
	for (std::shared_ptr<Game::Actor> actor : actorNeedToCheck)
	{
		glm::vec2 posCurrentActor = actor->GetPosition(), sizeCurrentActor = actor->GetSize();
		if ((nextPosition.x + sizeActor.x > posCurrentActor.x && nextPosition.x < posCurrentActor.x)
			|| (nextPosition.x + sizeActor.x < posCurrentActor.x && nextPosition.x > posCurrentActor.x))
			return false;
		if ((nextPosition.y + sizeActor.y > posCurrentActor.y && nextPosition.y < posCurrentActor.y)
			|| (nextPosition.y + sizeActor.y < posCurrentActor.y && nextPosition.y > posCurrentActor.y))
			return false;
	}
	return true;
}

