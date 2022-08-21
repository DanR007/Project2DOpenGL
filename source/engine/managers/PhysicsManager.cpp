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

void PhysicsManager::IsOverlap(Game::Actor* checkActor)
{
	std::shared_ptr<Physics::Collider> checkCollider = checkActor->GetCollider();
	
	glm::vec2& sizeActor = checkCollider->GetSize(), checkPosition = checkActor->GetPosition();
	for (std::shared_ptr<Game::Actor> actor : all_actors)
	{
		std::shared_ptr<Physics::Collider> currentActorCollider = actor->GetCollider();
		glm::vec2 posCurrentActor = actor->GetPosition(), sizeCurrentActor = currentActorCollider->GetSize();
		if (/*(posCurrentActor.x + sizeCurrentActor.x >= nextPosition.x && posCurrentActor.x <= nextPosition.x &&
			posCurrentActor.y + sizeCurrentActor.y >= nextPosition.y && posCurrentActor.y <= nextPosition.y)
			|| (posCurrentActor.x + sizeCurrentActor.x >= nextPosition.x + sizeActor.x && posCurrentActor.x <= nextPosition.x + sizeActor.x &&
				posCurrentActor.y + sizeCurrentActor.y >= nextPosition.y + sizeActor.y && posCurrentActor.y <= nextPosition.y + sizeActor.y)*/
				//			checkActor != actor.get() &&
			((posCurrentActor.x <= checkPosition.x + sizeActor.x && posCurrentActor.x >= checkPosition.x && ((posCurrentActor.y >= checkPosition.y && posCurrentActor.y + sizeCurrentActor.y <= checkPosition.y + sizeActor.y)
				|| (posCurrentActor.y + sizeCurrentActor.y >= checkPosition.y && posCurrentActor.y <= checkPosition.y)
				|| (posCurrentActor.y + sizeCurrentActor.y >= checkPosition.y + sizeActor.y && posCurrentActor.y <= checkPosition.y + sizeActor.y)))
				|| (posCurrentActor.x + sizeCurrentActor.x >= checkPosition.x && posCurrentActor.x <= checkPosition.x && ((posCurrentActor.y >= checkPosition.y && posCurrentActor.y + sizeCurrentActor.y <= checkPosition.y + sizeActor.y)
					|| (posCurrentActor.y + sizeCurrentActor.y >= checkPosition.y && posCurrentActor.y <= checkPosition.y)
					|| (posCurrentActor.y + sizeCurrentActor.y >= checkPosition.y + sizeActor.y && posCurrentActor.y <= checkPosition.y + sizeActor.y))))
			&& checkCollider->GetResponseType(currentActorCollider->GetObjectType()) == EResponseType::ERT_Overlap

			//|| (posCurrentActor.y <= nextPosition.y + sizeActor.y && posCurrentActor.y >= nextPosition.y && posCurrentActor.x >= nextPosition.x && posCurrentActor.x + sizeCurrentActor.x <= nextPosition.x + sizeActor.x)
			//|| (posCurrentActor.y + sizeCurrentActor.y >= nextPosition.y && posCurrentActor.y <= nextPosition.y && posCurrentActor.x >= nextPosition.x && posCurrentActor.x + sizeCurrentActor.x <= nextPosition.x + sizeActor.x)
			//|| (posCurrentActor.y >= nextPosition.y && posCurrentActor.y + sizeCurrentActor.y <= nextPosition.y + sizeActor.y)
			/* || (posCurrentActor.x + sizeCurrentActor.x >= nextPosition.x && posCurrentActor.x <= nextPosition.x &&
				posCurrentActor.y + sizeCurrentActor.y >= nextPosition.y + sizeActor.y && posCurrentActor.y <= nextPosition.y + sizeActor.y)
			|| (posCurrentActor.x + sizeCurrentActor.x >= nextPosition.x + sizeActor.x && posCurrentActor.x <= nextPosition.x + sizeActor.x &&
				posCurrentActor.y + sizeCurrentActor.y >= nextPosition.y && posCurrentActor.y <= nextPosition.y)*/


			)
			checkActor->Overlap(actor);
	}
}

