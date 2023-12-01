#include "Stone.h"

#include "../../../../main.h"

#include "../../../../engine/managers/GameManager.h"

Stone::Stone(const glm::ivec2& position):
	Resource("stone", position, GetWorld()->GetBlockSize(), 0.f)
{

}

Stone::~Stone()
{
#ifdef DEBUG_DESTRUCTOR
	std::cout << "Destroy Stone" << std::endl;
#endif
}
