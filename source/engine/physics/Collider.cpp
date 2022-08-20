#include "Collider.h"


namespace Physics
{
	void Collider::SetCollisionResponse(EObjectTypes objectType, EResponseType responseType)
	{
		objects_response_map[objectType] = responseType;
	}

}