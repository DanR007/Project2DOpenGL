#include "Resource.h"

#include "../../engine/physics/Collider.h"

#include "../../engine/managers/GameManager.h"

#include "../../main.h"

Resource::Resource(const std::string& init_sprite_name, const glm::ivec2& position, const glm::vec2& size, const float& rotation):
	Actor(init_sprite_name, GetWorld()->ConvertToWindowSpace(position), size, rotation)
{
	_resources_count = _max_resources_count;

	_collider = GetEngine()->GetPhysicsManager()->CreateCollider(EObjectTypes::EOT_StaticObject, this, GetWorld()->ConvertToWindowSpace(position), size);

	_components.push_back(_collider);
}

Resource::~Resource()
{
#ifdef DEBUG
	std::cout << "Destroy Resources" << std::endl;
#endif
}
