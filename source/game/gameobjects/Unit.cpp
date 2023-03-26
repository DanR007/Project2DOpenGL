#include "Unit.h"

#include "../../engine/controllers/Controller.h"
#include "../../engine/physics/Collider.h"

Unit::Unit(std::shared_ptr<Renderer::Texture2D> texture, std::shared_ptr<Renderer::ShaderProgram> shader, const std::string& initSubtextureName, const glm::vec2& startPosition, const glm::vec2& startSize, const float& startRotation)
	:Pawn(texture, shader, initSubtextureName, startPosition, startSize, startRotation)
{
	_choicing = false;
	_hp = 100;

	_controller = new Controller(this, 0);
	_collider = std::make_shared<Physics::Collider>(EObjectTypes::EOT_Pawn, this, startPosition);
}