#include "Goal.h"

#include "../../engine/managers/ResourcesManager.h"
#include "../../engine/managers/GameManager.h"

#include "../../engine/physics/Collider.h"

Goal::Goal(std::shared_ptr<Renderer::Texture2D> texture, std::shared_ptr<Renderer::ShaderProgram> shader,
	const std::string& initSubtextureName,
	const glm::vec2& startPosition, const glm::vec2& startSize, const float startRotation)
	:Actor(texture, shader, initSubtextureName, startPosition, startSize, startRotation)
{
	_collider = std::make_shared<Physics::Collider>(EObjectTypes::EOT_InteractiveObject, this, startPosition, startSize);
}
