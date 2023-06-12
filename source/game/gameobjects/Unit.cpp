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
	_selected_sprite = GetEngine()->GetRenderManager()->CreateSprite<Renderer::Sprite>(this, startPosition, startSize, "selected");
	
	_components.push_back(_selected_sprite);

	_map_position = GetWorld()->ConvertToMapSpace(startPosition);

	_is_selected = false;
	_hp = 100;

	_controller = new Controller(this, 0);
	_controller->SetMoveSpeed(20.f);
	_collider = std::make_shared<Physics::Collider>(EObjectTypes::EOT_Pawn, this, startPosition, startSize);
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
	//_selected_sprite->SetNeedToRender(_is_selected);
}

void Unit::Move(const glm::vec2& position)
{
	SetPosition(position);
	_selected_sprite->SetPosition(_world_position);
}

void Unit::MoveTo(const Cell& cell)
{
	if (GetController()->GetPathComplete())
	{
		_controller->MakePathForGoal(cell, _map_position);
	}
	else
	{
		_controller->MakePathForGoal(cell, GetController()->GetMapGoal());
	}
}

void Unit::PathComplete()
{
#ifdef DEBUG
	std::cout << "Path Complete" << std::endl;
#endif
	_goal->Destroy();
#ifdef DEBUG
	
	std::cout << "Destroy Goal" << std::endl;
#endif
	_goal = nullptr;
}
