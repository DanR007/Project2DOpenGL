#include "MeleeEnemy.h"

#include "../../engine/managers/GameManager.h"

#include "../../engine/physics/Collider.h"

#include "../HealthComponent.h"

#include "../../engine/controllers/EnemyController.h"

#include <cmath>
#include <iostream>
namespace Game
{
	MeleeEnemy::MeleeEnemy(std::shared_ptr<Renderer::Texture2D> texture, std::shared_ptr<Renderer::ShaderProgram> shader, 
		const std::string& initSubtextureName,
		const glm::vec2& startPosition, const glm::vec2& startSize, const float startRotation, const float move_speed)
		: Enemy(std::move(texture), std::move(shader), initSubtextureName, startPosition, startSize, startRotation)
	{
		_collider = std::make_shared<Physics::Collider>(EObjectTypes::EOT_Enemy, startPosition, startSize);
		_collider->SetCollisionResponse(EObjectTypes::EOT_Character, EResponseType::ERT_Overlap);
		_collider->SetCollisionResponse(EObjectTypes::EOT_Enemy, EResponseType::ERT_Ignore);
		
		_collider->Attach(this);

		_health = 1;

		_controller = new EnemyController(this, move_speed);
	}

	MeleeEnemy::~MeleeEnemy()
	{
		if (_controller)
		{
			delete _controller;
			_controller = nullptr;
		}
	}

	
}