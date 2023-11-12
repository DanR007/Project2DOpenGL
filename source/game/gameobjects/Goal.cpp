#include "Goal.h"

#include "../../engine/managers/ResourcesManager.h"
#include "../../engine/managers/GameManager.h"

#include "../../engine/renderer/AnimSprite.h"

#include "../../engine/physics/Collider.h"

#include "Unit.h"

#include <iostream>

Goal::Goal(const std::string& initSubtextureName
		, const glm::vec2& startPosition
		, const glm::vec2& startSize
		, const uint8_t& render_layer
		, const float startRotation)
	:Actor(initSubtextureName, startPosition, startSize, render_layer, startRotation)
{
	
}
Goal::Goal(const glm::ivec2& position) :
	Goal("goal", GetWorld()->ConvertToWindowSpace(position), GetWorld()->GetBlockSize(), 0)
{
	std::cout << "Create Goal " << std::endl;
}

void Goal::Update(const float& deltaTime)
{
	if (_unit)
	{
		GetAnimSprite()->SetNeedToRender(_unit->GetIsSelected());
	}
}

