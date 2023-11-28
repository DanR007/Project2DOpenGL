#include "Unit.h"
#include "../Goal.h"

#include "../../../engine/controllers/Controller.h"
#include "../../../engine/physics/Collider.h"

#include "../../../engine/managers/RenderManager.h"
#include "../../../engine/managers/EngineManager.h"
#include "../../../engine/managers/GameManager.h"

#include "../../../main.h"

#include <iostream>

Unit::Unit(const std::string& initSubtextureName
		, const glm::vec2& startPosition
		, const glm::vec2& startSize
		, const uint8_t& render_layer
		, const float startRotation)
	:Pawn(initSubtextureName, startPosition, startSize, render_layer, startRotation)
{
	_controller = new Controller(this, 0);
	_controller->SetMoveSpeed(20.f);
}

Unit::Unit(const glm::ivec2& position)
	: Unit("mush1", GetEngine()->GetWorld()->ConvertToWindowSpace(position),
		GetEngine()->GetWorld()->GetBlockSize(), DYNAMIC, 0.f)
{
	_map_position = position;
}

Unit::Unit(Unit&& u) noexcept :
	Pawn(std::move(u))
{
	_is_selected = u._is_selected;
	_hp = u._hp;
}

Unit::~Unit()
{
#ifdef DEBUG
	std::cout << "Destroy Unit" << std::endl;
#endif
}

void Unit::Update(const float& deltaTime)
{
	Pawn::Update(deltaTime);
}

void Unit::MoveTo(Cell* cell)
{
#ifdef DEBUG_PATH_SEARCHING
	std::cout << "Call MoveTo" << std::endl;
#endif //DEBUG
	if (GetController())
	{
		if (GetController()->GetPathComplete())
		{
			GetController()->MakePathForGoal(cell, _map_position);
		}
		else
		{
			GetController()->MakePathForGoal(cell, GetController()->GetMapNode());
		}
	}
}

void Unit::MakePathComplete()
{
	_goal->Destroy();
	_goal = nullptr;
}
