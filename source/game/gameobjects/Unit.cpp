#include "Unit.h"
#include "Goal.h"

#include "../../engine/controllers/Controller.h"
#include "../../engine/physics/Collider.h"

#include "../../engine/renderer/AnimSprite.h"

#include "../../engine/managers/GameManager.h"

#include <iostream>

Unit::Unit(std::shared_ptr<Renderer::Texture2D> texture, std::shared_ptr<Renderer::ShaderProgram> shader, const std::string& initSubtextureName, 
	const glm::vec2& startPosition, const glm::vec2& startSize, const float& startRotation)
	:Pawn(texture, shader, initSubtextureName, startPosition, startSize, startRotation)
{
	_selected_sprite = std::make_unique<Renderer::Sprite>(texture, shader, "selected", this, startPosition, startSize);

	_map_position = glm::ivec2((startPosition.x + GetWorld()->GetOffset().x) / GetWorld()->GetBlockSize().x, 
		(startPosition.y + GetWorld()->GetOffset().y) / GetWorld()->GetBlockSize().y);

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
	_controller->MakePathForGoal(cell, _map_position);
}

void Unit::PathComplete()
{
	std::cout << "Path Complete" << std::endl;
	_goal->DestroyActor();
	_goal = nullptr;
}
