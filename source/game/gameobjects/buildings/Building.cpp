#include "Building.h"

#include "../../../main.h"

#include "../../../engine/managers/EngineManager.h"
#include "../../../engine/managers/GameManager.h"

Building::Building(const glm::ivec2& pivot_position, const glm::ivec2& size, const EBuildingType& type)
	:Building("", GetEngine()->GetWorld()->ConvertToWindowSpace(pivot_position) - glm::vec2(GetEngine()->GetWorld()->GetBlockSize().x * size.x, 0),
		glm::vec2(GetEngine()->GetWorld()->GetBlockSize().x * size.x, 
			GetEngine()->GetWorld()->GetBlockSize().y * size.y))
{
	_building_size = size;
	_type = type;
}

Building::Building(const std::string& initSubtextureName, const glm::vec2& startPosition,
	const glm::vec2& startSize, const float& rotation)
	:Pawn(initSubtextureName, startPosition, startSize, rotation)
{

}

Building::~Building()
{
}
