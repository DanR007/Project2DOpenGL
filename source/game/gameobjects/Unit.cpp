#include "Unit.h"

#include "../../engine/controllers/Controller.h"
#include "../../engine/physics/Collider.h"

#include "../../engine/renderer/AnimSprite.h"

#include "../../engine/managers/GameManager.h"

Unit::Unit(std::shared_ptr<Renderer::Texture2D> texture, std::shared_ptr<Renderer::ShaderProgram> shader, const std::string& initSubtextureName, 
	const glm::vec2& startPosition, const glm::vec2& startSize, const float& startRotation)
	:Pawn(texture, shader, initSubtextureName, startPosition, startSize, startRotation)
{
	_map_position = glm::ivec2((startPosition.x + GetWorld()->GetOffset().x) / GetWorld()->GetBlockSize().x, 
		(startPosition.y + GetWorld()->GetOffset().y) / GetWorld()->GetBlockSize().y);

	_is_choicing = false;
	_hp = 100;

	_controller = new Controller(this, 0);
	_collider = std::make_shared<Physics::Collider>(EObjectTypes::EOT_Pawn, this, startPosition, startSize);
}

Unit::Unit(Unit&& u) noexcept :
	Pawn(std::move(u))
{
	_is_choicing = u._is_choicing;
	_hp = u._hp;
}

void Unit::MoveTo(const Cell& cell)
{
	_controller->MakePathForGoal(cell, _map_position);
}
