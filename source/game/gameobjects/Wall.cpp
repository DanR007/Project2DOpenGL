#include "Wall.h"

#include "../../engine/managers/ResourcesManager.h"
#include "../../engine/managers/GameManager.h"

#include "../../engine/physics/Collider.h"

Wall::Wall(const std::string& initSubtextureName,
	const glm::vec2& startPosition, const glm::vec2& startSize, const float startRotation)
	:Actor(initSubtextureName, startPosition, startSize, startRotation)
{
	_collider = new Physics::Collider(EObjectTypes::EOT_InteractiveObject, this, startPosition, startSize);
}

Wall::~Wall()
{
#ifdef DEBUG
	std::cout << "Destroy Wall" << std::endl;
#endif
}
