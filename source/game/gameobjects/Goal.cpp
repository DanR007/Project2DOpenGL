#include "Goal.h"

#include "../../engine/managers/ResourcesManager.h"
#include "../../engine/managers/GameManager.h"
#include "../../engine/managers/RenderManager.h"

#include "../../engine/renderer/AnimSprite.h"

#include "../../engine/physics/Collider.h"

#include "units/Unit.h"

#include <iostream>

Goal::Goal(const std::string& initSubtextureName
		, const glm::vec2& startPosition
		, const glm::vec2& startSize
		, const float startRotation)
	:Actor(initSubtextureName, startPosition, startSize, STATIC, startRotation)
{
	
}
Goal::Goal(const glm::ivec2& position) :
	Goal("goal", GetWorld()->ConvertToWindowSpace(position), GetWorld()->GetBlockSize())
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

