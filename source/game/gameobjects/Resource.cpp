#include "Resource.h"

#include "../../engine/physics/Collider.h"

#include "../../engine/managers/GameManager.h"

#include "../../engine/AI/NavMesh.h"

#include "../../main.h"

#include "../../engine/generators/RTSMapGenerator.h"

Resource::Resource(const std::string& init_sprite_name
		, const glm::vec2& startPosition
		, const glm::vec2& startSize
		, const uint8_t& render_layer
		, const float startRotation):
		Actor(init_sprite_name, startPosition, startSize, render_layer, startRotation)
{
	_collider = GetEngine()->GetPhysicsManager()->CreateCollider(EObjectTypes::EOT_StaticObject, this, startPosition, startSize);
	_components.push_back(_collider);

	_resources_count = _max_resources_count;
}

Resource::Resource(const std::string& init_sprite_name, const glm::ivec2& position, const glm::vec2& size, const float& rotation):
	Resource(init_sprite_name, GetWorld()->ConvertToWindowSpace(position), size)
{
	_cell = GetEngine()->GetWorld()->GetMap()[position.y][position.x];
}

Resource::~Resource()
{
#ifdef DEBUG
	std::cout << "Destroy Resources" << std::endl;
#endif
}

void Resource::SetCell(Cell* cell)
{
	_cell = cell;
}

void Resource::SetEmpty()
{
	if(_cell)
	{
		GetEngine()->GetWorld()->GetNavMesh()->ClearMapCell(_cell->_position);
	}
	else
	{
#ifdef DEBUG
		std::cout << "_cell is nullptr" << std::endl;
#endif // DEBUG
	}
	Destroy();
}
