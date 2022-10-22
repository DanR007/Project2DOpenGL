#include "Collider.h"

#include "../../game/AllObjects.h"
#include "../default_classes/Actor.h"

#include "../managers/GameManager.h"
namespace Physics
{
	void Collider::SetCollisionResponse(EObjectTypes objectType, EResponseType responseType)
	{
		objects_response_map[objectType] = responseType;
	}

	std::shared_ptr<Game::Actor> Collider::GetOwner()
	{
		for (std::shared_ptr<Game::Actor> actor : GameManager::_all_actors)
		{
			if (actor->GetCollider().get() == this)
				return actor;
		}
		return nullptr;
	}

}