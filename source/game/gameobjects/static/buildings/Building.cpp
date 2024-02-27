#include "Building.h"

#include "../../../../main.h"

#include "../../../../engine/managers/EngineManager.h"
#include "../../../../engine/managers/GameManager.h"
#include "../../../../engine/managers/PhysicsManager.h"
#include "../../../../engine/managers/RenderManager.h"

#include "../../../../engine/AI/NavMesh.h"

#include "../../units/Worker.h"

std::map<EBuildingType, std::string> _building_sprite_name = {
	{EBuildingType::EBT_Lumber, "lumber"},
	{EBuildingType::EBT_Quarry, "quarry"},
	{EBuildingType::EBT_Barracks, "barracks"},
	{EBuildingType::EBT_None, ""}
};

Building::Building(const glm::ivec2& pivot_position, const glm::ivec2& size, const EBuildingType& type)
	:Building(
	_building_sprite_name[type]
	, GetEngine()->GetWorld()->ConvertToWindowSpace(pivot_position) - glm::vec2((GetEngine()->GetWorld()->GetBlockSize().x) * (size.x - 1), 0)
	, glm::vec2(GetEngine()->GetWorld()->GetBlockSize().x * size.x, GetEngine()->GetWorld()->GetBlockSize().y * size.y)
	, STATIC
	)
{
	_building_size = size;
	_type = type;
}

Building::Building(const std::string& initSubtextureName
		, const glm::vec2& startPosition
		, const glm::vec2& startSize
		, const uint8_t& render_layer
		, const float startRotation)
	:Pawn(initSubtextureName, startPosition, startSize, render_layer, startRotation)
{
	
}

Building::~Building()
{
	for(int x = 0; x < _building_size.x; ++x)
	{
		for(int y = 0; y < _building_size.y; ++y)
		{
			glm::ivec2 pos(_map_position + glm::ivec2(x, y));

			GetWorld()->GetNavMesh()->ClearMapCell(pos);
		}
	}

	if (_worker)
	{
		_worker->Destroy();
	}
}

bool Building::CanReplace()
{
	for (int i = 0; i < _building_size.y; i++)
	{
		for (int j = 0; j < _building_size.x; j++)
		{
			glm::ivec2 check_pos = glm::ivec2(_map_position.x + j, _map_position.y + i);
			if (!(GetEngine()->GetWorld()->GetNavMesh()->InMap(check_pos) 
			&& GetEngine()->GetWorld()->GetNavMesh()->IsFreeCell(check_pos)))
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

void Building::Replace()
{
	Pawn::Replace();

	_selected_sprite->SetPosition(GetAnimSprite()->GetPosition());

	for(int x = 0; x < _building_size.x; ++x)
	{
		for(int y = 0; y < _building_size.y; ++y)
		{
			glm::ivec2 pos(_map_position);

			pos += glm::ivec2(x, y);

			GetWorld()->GetNavMesh()->SetMapCell(pos, 'r', this);
		}
	}

	if(_worker)
	{
		_worker->SetPlayerID(_player_id);
		_worker->Replace();
	}
}

glm::ivec2 Building::GetFreePositionAroundBuilding()
{
	glm::ivec2 free_position = glm::ivec2(-2);

	//проверка левой стороны
	for(int y = -1; y < _building_size.y + 1; ++y)
	{
		glm::ivec2 cur = glm::ivec2(_map_position.x - 1, _map_position.y + y);
		if(GetEngine()->GetWorld()->GetNavMesh()->IsFreeCell(cur))
		{
			return cur;
		}
	}
	//проверка правой стороны
	for(int y = -1; y < _building_size.y + 1; ++y)
	{
		glm::ivec2 cur = glm::ivec2(_map_position.x + _building_size.x + 1, _map_position.y + y);
		if(GetEngine()->GetWorld()->GetNavMesh()->IsFreeCell(cur))
		{
			return cur;
		}
	}

	//проверка нижней стороны
	for(int x = 0; x < _building_size.x; ++x)
	{
		glm::ivec2 cur = glm::ivec2(_map_position.x + x, _map_position.y - 1);
		if(GetEngine()->GetWorld()->GetNavMesh()->IsFreeCell(cur))
		{
			return cur;
		}
	}
	//проверка верхней стороны
	for(int x = 0; x < _building_size.x; ++x)
	{
		glm::ivec2 cur = glm::ivec2(_map_position.x + x, _map_position.y + _building_size.y + 1);
		if(GetEngine()->GetWorld()->GetNavMesh()->IsFreeCell(cur))
		{
			return cur;
		}
	}

	return free_position;
}