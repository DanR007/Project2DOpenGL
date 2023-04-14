#include "Unit.h"
#include "Goal.h"

#include "../../engine/controllers/Controller.h"
#include "../../engine/physics/Collider.h"

#include "../../engine/renderer/AnimSprite.h"

#include "../../engine/managers/GameManager.h"

#include <iostream>

Unit::Unit(const std::string& initSubtextureName, 
	const glm::vec2& startPosition, const glm::vec2& startSize, const float& startRotation)
	:Pawn(initSubtextureName, startPosition, startSize, startRotation)
{
	_selected_sprite = std::make_unique<Renderer::Sprite>(ResourcesManager::GetTexture("textureAtlas"), ResourcesManager::GetShaderProgram("spriteShader"), "selected", this, startPosition, startSize);

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
}

void Unit::Update(const float deltaTime)
{
	if (_is_selected)
	{
		_selected_sprite->Render();
	}
	Pawn::Update(deltaTime);
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
	_goal->DestroyActor();
#ifdef DEBUG
	
	std::cout << "Destroy Goal" << std::endl;
#endif
	_goal = nullptr;
}
