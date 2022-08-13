#include "PhysicsManager.h"
#include "../../game/Actor.h"

#include "../../main.h"

bool PhysicsManager::CanMove(std::vector<std::shared_ptr<Game::Actor>>& actorNeedToCheck, const glm::vec2& nextPosition, const glm::vec2& sizeActor)
{
	for (std::shared_ptr<Game::Actor> actor : actorNeedToCheck)
	{
		glm::vec2 posCurrentActor = actor->GetPosition(), sizeCurrentActor = actor->GetSize();
		if (/*(posCurrentActor.x + sizeCurrentActor.x >= nextPosition.x && posCurrentActor.x <= nextPosition.x &&
			posCurrentActor.y + sizeCurrentActor.y >= nextPosition.y && posCurrentActor.y <= nextPosition.y) 
			|| (posCurrentActor.x + sizeCurrentActor.x >= nextPosition.x + sizeActor.x && posCurrentActor.x <= nextPosition.x + sizeActor.x &&
				posCurrentActor.y + sizeCurrentActor.y >= nextPosition.y + sizeActor.y && posCurrentActor.y <= nextPosition.y + sizeActor.y)*/
			
			(posCurrentActor.x <= nextPosition.x + sizeActor.x && posCurrentActor.x >= nextPosition.x && ((posCurrentActor.y >= nextPosition.y && posCurrentActor.y + sizeCurrentActor.y <= nextPosition.y + sizeActor.y) || 
				(posCurrentActor.y + sizeCurrentActor.y >= nextPosition.y && posCurrentActor.y <= nextPosition.y) 
				|| (posCurrentActor.y + sizeCurrentActor.y >= nextPosition.y + sizeActor.y && posCurrentActor.y <= nextPosition.y + sizeActor.y)))
			|| (posCurrentActor.x + sizeCurrentActor.x >= nextPosition.x && posCurrentActor.x <= nextPosition.x && ((posCurrentActor.y >= nextPosition.y && posCurrentActor.y + sizeCurrentActor.y <= nextPosition.y + sizeActor.y)
				|| (posCurrentActor.y + sizeCurrentActor.y >= nextPosition.y && posCurrentActor.y <= nextPosition.y)
				|| (posCurrentActor.y + sizeCurrentActor.y >= nextPosition.y + sizeActor.y && posCurrentActor.y <= nextPosition.y + sizeActor.y)))

			//|| (posCurrentActor.y <= nextPosition.y + sizeActor.y && posCurrentActor.y >= nextPosition.y && posCurrentActor.x >= nextPosition.x && posCurrentActor.x + sizeCurrentActor.x <= nextPosition.x + sizeActor.x)
			//|| (posCurrentActor.y + sizeCurrentActor.y >= nextPosition.y && posCurrentActor.y <= nextPosition.y && posCurrentActor.x >= nextPosition.x && posCurrentActor.x + sizeCurrentActor.x <= nextPosition.x + sizeActor.x)
			//|| (posCurrentActor.y >= nextPosition.y && posCurrentActor.y + sizeCurrentActor.y <= nextPosition.y + sizeActor.y)
			/* || (posCurrentActor.x + sizeCurrentActor.x >= nextPosition.x && posCurrentActor.x <= nextPosition.x &&
				posCurrentActor.y + sizeCurrentActor.y >= nextPosition.y + sizeActor.y && posCurrentActor.y <= nextPosition.y + sizeActor.y)
			|| (posCurrentActor.x + sizeCurrentActor.x >= nextPosition.x + sizeActor.x && posCurrentActor.x <= nextPosition.x + sizeActor.x &&
				posCurrentActor.y + sizeCurrentActor.y >= nextPosition.y && posCurrentActor.y <= nextPosition.y)*/

			
			)
			return false;
	}
	return true;
}

