#include "Collider.h"

#include "../../game/AllObjects.h"
#include "../../game/Actor.h"

namespace Physics
{
	void Collider::SetCollisionResponse(EObjectTypes objectType, EResponseType responseType)
	{
		objects_response_map[objectType] = responseType;
	}

	std::shared_ptr<Game::Actor> Collider::GetOwner()
	{
		for (std::shared_ptr<Game::Actor> actor : all_actors)
		{
			if (actor->GetCollider().get() == this)
				return actor;
		}
		return nullptr;
	}

}