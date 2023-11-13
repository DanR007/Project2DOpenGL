#include "Wood.h"

#include "../../../../main.h"

#include "../../../../engine/managers/GameManager.h"

Wood::Wood(const glm::ivec2& position):
	Resource("tree", position, GetWorld()->GetBlockSize(), 0.f)
{
}

Wood::~Wood()
{
#ifdef DEBUG
	std::cout << "Destroy Wood" << std::endl;
#endif
}
