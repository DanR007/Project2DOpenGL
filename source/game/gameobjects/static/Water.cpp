#include "Water.h"

#include "../../../main.h"

#include "../../../engine/managers/GameManager.h"
#include "../../../engine/managers/RenderManager.h"

Water::Water(const glm::ivec2& position):
	Water("water", GetWorld()->ConvertToWindowSpace(position), GetEngine()->GetWorld()->GetBlockSize(), MAP_CELL)
{
}

Water::Water(const std::string& initSubtextureName,
	const glm::vec2& startPosition, const glm::vec2& startSize, const uint8_t& render_layer)
    : Actor(initSubtextureName, startPosition, startSize, render_layer)
{

}
Water::~Water()
{
#ifdef DEBUG_DESTRUCTOR
	std::cout << "Destroy Water" << std::endl;
#endif
}