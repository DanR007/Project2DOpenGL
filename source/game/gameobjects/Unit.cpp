#include "Unit.h"
#include "Goal.h"

#include "../../engine/controllers/Controller.h"
#include "../../engine/physics/Collider.h"

#include "../../engine/managers/RenderManager.h"
#include "../../engine/managers/EngineManager.h"
#include "../../engine/managers/GameManager.h"

#include "../../main.h"

#include <iostream>

Unit::Unit(const std::string& initSubtextureName, 
	const glm::vec2& startPosition, const glm::vec2& startSize, const float& startRotation)
	:Pawn(initSubtextureName, startPosition, startSize, startRotation)
{
	_hp = 100;

	_controller = new Controller(this, 0);
	_controller->SetMoveSpeed(20.f);

	_collider = GetEngine()->GetPhysicsManager()->CreateCollider(EObjectTypes::EOT_Pawn, this, startPosition, startSize);

	_components.push_back(_collider);
}

Unit::Unit(const glm::ivec2& position)
	: Unit("mush1", GetEngine()->GetWorld()->ConvertToWindowSpace(position),
		GetEngine()->GetWorld()->GetBlockSize(), 0.f)
{
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
	_selected_sprite->SetNeedToRender(_is_selected);
}

void Unit::Move(const glm::vec2& position)
{
	SetPosition(position);
	_selected_sprite->SetPosition(_world_position);
}

void Unit::MoveTo(Cell* cell)
{
	if (GetController() && GetController()->GetPathComplete())
	{
		GetController()->MakePathForGoal(cell, _map_position);
	}
	else
	{
		GetController()->MakePathForGoal(cell, GetController()->GetMapGoal());
	}
}

void Unit::PathComplete()
{
	_goal->Destroy();
	_goal = nullptr;
}
