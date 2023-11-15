#include "Resource.h"

#include "../../../../engine/physics/Collider.h"

#include "../../../../engine/managers/GameManager.h"
#include "../../../../engine/managers/RenderManager.h"

#include "../../../../engine/AI/NavMesh.h"

#include "../../../../main.h"

#include "../../../../engine/generators/RTSMapGenerator.h"

#include "../../units/Worker.h"

Resource::Resource(const std::string& init_sprite_name
		, const glm::vec2& startPosition
		, const glm::vec2& startSize
		, const uint8_t& render_layer
		, const float startRotation):
		Actor(init_sprite_name, startPosition, startSize, STATIC, startRotation)
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
	_worker_on_this_resource.clear();
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
		std::vector<Worker*>::iterator it = _worker_on_this_resource.begin();

		for(; it != _worker_on_this_resource.end(); ++it)
		{
			std::cout << "Set empty" << std::endl;
			(*it)->SetEmptyResource();
			
		}
	}
	else
	{
#ifdef DEBUG
		std::cout << "_cell is nullptr" << std::endl;
#endif // DEBUG
	}
	Destroy();
}

void Resource::NewWorker(Worker* worker)
{
	_worker_on_this_resource.push_back(worker);
}
