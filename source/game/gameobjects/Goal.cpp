#include "Goal.h"

#include "../../engine/managers/ResourcesManager.h"
#include "../../engine/managers/GameManager.h"

#include "../../engine/renderer/AnimSprite.h"

#include "../../engine/physics/Collider.h"

#include "Unit.h"

#include <iostream>

Goal::Goal(const std::string& initSubtextureName,
	const glm::vec2& startPosition, const glm::vec2& startSize, const float startRotation)
	:Actor(initSubtextureName, startPosition, startSize, startRotation)
{
	_collider = std::make_shared<Physics::Collider>(EObjectTypes::EOT_InteractiveObject, this, startPosition, startSize);
	std::cout << "Create Goal " << std::endl;
}
Goal::Goal(const glm::ivec2& position) :
	Actor("goal", GetWorld()->ConvertToWindowSpace(position), GetWorld()->GetBlockSize(), 0)
{
	_collider = std::make_shared<Physics::Collider>(EObjectTypes::EOT_InteractiveObject, this, GetWorld()->ConvertToWindowSpace(position), GetWorld()->GetBlockSize());
	std::cout << "Create Goal " << std::endl;
}

void Goal::Update(float deltaTime)
{
	if (_unit && _unit->GetIsSelected())
	{
		_anim_sprite->Update(deltaTime);
	}
}
