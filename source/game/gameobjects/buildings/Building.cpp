#include "Building.h"

#include "../../../main.h"

#include "../../../engine/managers/EngineManager.h"
#include "../../../engine/managers/GameManager.h"
#include "../../../engine/managers/PhysicsManager.h"
#include "../../../engine/managers/RenderManager.h"

#include "../../../engine/physics/Collider.h"

#include "../../../engine/AI/NavMesh.h"

#include "../units/Worker.h"

std::map<EBuildingType, std::string> _building_sprite_name = {
	{EBuildingType::EBT_Lumber, "lumber"},
	{EBuildingType::EBT_Quary, "quary"},
	{EBuildingType::EBT_None, ""}
};

Building::Building(const glm::ivec2& pivot_position, const glm::ivec2& size, const EBuildingType& type)
	:Building(_building_sprite_name[type], GetEngine()->GetWorld()->ConvertToWindowSpace(pivot_position) - glm::vec2((GetEngine()->GetWorld()->GetBlockSize().x - 1) * size.x, 0),
		glm::vec2(GetEngine()->GetWorld()->GetBlockSize().x * size.x, 
			GetEngine()->GetWorld()->GetBlockSize().y * size.y))
{
	_building_size = size;
	_type = type;
}

bool Building::CanReplace()
{
	for (int i = 0; i < _building_size.y; i++)
	{
		for (int j = 0; j < _building_size.x; j++)
		{
			if (GetEngine()->GetWorld()->GetMap()[_map_position.y + i][_map_position.x + j]->_symbol != ' ')
			{
				return false;
			}
		}
	}
	return true;
}

void Building::Update(const float& deltaTime)
{
	Pawn::Update(deltaTime);
	_selected_sprite->SetNeedToRender(_is_selected);
}

Building::Building(const std::string& initSubtextureName, const glm::vec2& startPosition,
	const glm::vec2& startSize, const float& rotation)
	:Pawn(initSubtextureName, startPosition, startSize, rotation)
{
	_collider = GetEngine()->GetPhysicsManager()->CreateCollider(EObjectTypes::EOT_Pawn, this, startPosition, startSize);
}

Building::~Building()
{
	if (_worker)
	{
		_worker->Destroy();
	}
}

void Building::Replace()
{
	_replace = true;
}
