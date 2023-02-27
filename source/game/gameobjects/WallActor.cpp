#include "WallActor.h"

#include "../../engine/physics/Collider.h"

namespace Game
{
	namespace Objects
	{
		Wall::Wall(std::shared_ptr<Renderer::Texture2D> texture, std::shared_ptr<Renderer::ShaderProgram> shader,
			const std::string& initSubtextureName,
			const glm::vec2& startPosition, const glm::vec2& startSize, const float startRotation)
			:Actor(std::move(texture), std::move(shader), initSubtextureName, startPosition, startSize, startRotation)
		{
			_collider = std::make_shared<Physics::Collider>(EObjectTypes::EOT_StaticObject, this, startPosition, startSize, startRotation);
		}
	}
}