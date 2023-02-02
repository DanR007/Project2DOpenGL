#include "PistolBullet.h"
#include "../../engine/physics/Collider.h"

#include "../enemies/Enemy.h"

#include "../HealthComponent.h"

#include <iostream>
namespace Game
{
	PistolBullet::PistolBullet(std::shared_ptr<Renderer::Texture2D> texture, std::shared_ptr<Renderer::ShaderProgram> shader, 
		const std::string& initSubtextureName, const glm::vec2& startPosition, const glm::vec2& startSize, const float startRotation)
		:Bullet(std::move(texture), std::move(shader), initSubtextureName, startPosition, startSize, startRotation)
	{
		_collider = std::make_shared<Physics::Collider>(EObjectTypes::EOT_Projectile, this, startPosition, startSize);

		_collider->SetCollisionResponse(EObjectTypes::EOT_Enemy, EResponseType::ERT_Overlap);
		_collider->SetCollisionResponse(EObjectTypes::EOT_Character, EResponseType::ERT_Ignore);
		_collider->SetCollisionResponse(EObjectTypes::EOT_StaticObject, EResponseType::ERT_Overlap);
		_collider->SetCollisionResponse(EObjectTypes::EOT_Projectile, EResponseType::ERT_Ignore);
	}

	void PistolBullet::Overlap(Actor* overlappingActor)
	{
		if (dynamic_cast<Enemy*>(overlappingActor))
		{
			dynamic_cast<Enemy*>(overlappingActor)->Hurt(_damage);
		}

		DestroyActor();
	}
}
