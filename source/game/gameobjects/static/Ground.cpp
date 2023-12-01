#include "Ground.h"

#include "../../../main.h"

#include "../../../engine/managers/GameManager.h"
#include "../../../engine/managers/RenderManager.h"

Ground::Ground(const glm::ivec2& position):
	Ground("ground", GetWorld()->ConvertToWindowSpace(position), GetEngine()->GetWorld()->GetBlockSize(), MAP_CELL)
{
}

Ground::Ground(const std::string& initSubtextureName,
	const glm::vec2& startPosition, const glm::vec2& startSize, const uint8_t& render_layer)
    : Actor(initSubtextureName, startPosition, startSize, render_layer)
{

}

Ground::~Ground()
{
#ifdef DEBUG_DESTRUCTOR
	std::cout << "Destroy Ground" << std::endl;
#endif
}