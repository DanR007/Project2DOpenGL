#include "PhysicsManager.h"
#include "GameManager.h"

#include "../../game/Actor.h"

#include "../physics/Collider.h"

#include "../../main.h"

bool PhysicsManager::CanMove(Game::Actor* checkActor, const glm::vec2& nextPosition)
{
	std::shared_ptr<Physics::Collider> checkCollider = checkActor->GetCollider();
	glm::vec2& sizeActor = checkCollider->GetSize();
	for (std::shared_ptr<Game::Actor> actor : all_actors)
	{
		std::shared_ptr<Physics::Collider> currentActorCollider = actor->GetCollider();
		glm::vec2 posCurrentActor = actor->GetPosition(), sizeCurrentActor = currentActorCollider->GetSize();
		if (/*(posCurrentActor.x + sizeCurrentActor.x >= nextPosition.x && posCurrentActor.x <= nextPosition.x &&
			posCurrentActor.y + sizeCurrentActor.y >= nextPosition.y && posCurrentActor.y <= nextPosition.y) 
			|| (posCurrentActor.x + sizeCurrentActor.x >= nextPosition.x + sizeActor.x && posCurrentActor.x <= nextPosition.x + sizeActor.x &&
				posCurrentActor.y + sizeCurrentActor.y >= nextPosition.y + sizeActor.y && posCurrentActor.y <= nextPosition.y + sizeActor.y)*/
//			checkActor != actor.get() &&
			((posCurrentActor.x <= nextPosition.x + sizeActor.x && posCurrentActor.x >= nextPosition.x && ((posCurrentActor.y >= nextPosition.y && posCurrentActor.y + sizeCurrentActor.y <= nextPosition.y + sizeActor.y) 
				|| (posCurrentActor.y + sizeCurrentActor.y >= nextPosition.y && posCurrentActor.y <= nextPosition.y) 
				|| (posCurrentActor.y + sizeCurrentActor.y >= nextPosition.y + sizeActor.y && posCurrentActor.y <= nextPosition.y + sizeActor.y)))
			|| (posCurrentActor.x + sizeCurrentActor.x >= nextPosition.x && posCurrentActor.x <= nextPosition.x && ((posCurrentActor.y >= nextPosition.y && posCurrentActor.y + sizeCurrentActor.y <= nextPosition.y + sizeActor.y)
				|| (posCurrentActor.y + sizeCurrentActor.y >= nextPosition.y && posCurrentActor.y <= nextPosition.y)
				|| (posCurrentActor.y + sizeCurrentActor.y >= nextPosition.y + sizeActor.y && posCurrentActor.y <= nextPosition.y + sizeActor.y)))) 
			&& checkCollider->GetResponseType(currentActorCollider->GetObjectType()) == EResponseType::ERT_Block

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

void PhysicsManager::IsOverlap(std::shared_ptr<Physics::Collider> checkCollider)
{
	std::shared_ptr<Game::Actor> ownerCollider;
	glm::vec2& sizeActor = checkCollider->GetSize(), checkPosition = checkCollider->GetPosition();
	std::vector<std::shared_ptr<Game::Actor>>::iterator it = all_actors.begin();
	for (; it < all_actors.end(); it++)
	{
		std::shared_ptr<Physics::Collider> currentActorCollider = it->get()->GetCollider();
		glm::vec2 posCurrentCollider = currentActorCollider->GetPosition(), sizeCurrentCollider = currentActorCollider->GetSize();
		if (
			((posCurrentCollider.x <= checkPosition.x + sizeActor.x && posCurrentCollider.x >= checkPosition.x && ((posCurrentCollider.y >= checkPosition.y && posCurrentCollider.y + sizeCurrentCollider.y <= checkPosition.y + sizeActor.y)
				|| (posCurrentCollider.y + sizeCurrentCollider.y >= checkPosition.y && posCurrentCollider.y <= checkPosition.y)
				|| (posCurrentCollider.y + sizeCurrentCollider.y >= checkPosition.y + sizeActor.y && posCurrentCollider.y <= checkPosition.y + sizeActor.y)))
				|| (posCurrentCollider.x + sizeCurrentCollider.x >= checkPosition.x && posCurrentCollider.x <= checkPosition.x && ((posCurrentCollider.y >= checkPosition.y && posCurrentCollider.y + sizeCurrentCollider.y <= checkPosition.y + sizeActor.y)
					|| (posCurrentCollider.y + sizeCurrentCollider.y >= checkPosition.y && posCurrentCollider.y <= checkPosition.y)
					|| (posCurrentCollider.y + sizeCurrentCollider.y >= checkPosition.y + sizeActor.y && posCurrentCollider.y <= checkPosition.y + sizeActor.y))))
			&& checkCollider->GetResponseType(currentActorCollider->GetObjectType()) == EResponseType::ERT_Overlap
			)
		{
			ownerCollider = checkCollider->GetOwner();
			if(ownerCollider)
				ownerCollider->Overlap(*it);
			break;
		}
			
	}
}

