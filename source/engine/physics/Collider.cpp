#include "Collider.h"

#include <algorithm>

namespace Physics
{
	void Collider::SetCollisionResponse(EObjectTypes objectType, EResponseType responseType)
	{
		objects_response_map[objectType] = responseType;
	}

	void Collider::Overlap(Actor* actor) 
	{ 
		_delegate_overlap(actor); 
		_overlapping_actors.push_back(actor);
	}
}