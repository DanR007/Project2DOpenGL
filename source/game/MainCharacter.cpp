#include "MainCharacter.h"

#include "HealthComponent.h"

#include "weapons/WeaponComponent.h"

#include "enemies/MeleeEnemy.h"

#include "gameobjects/HealActor.h"

#include "../engine/renderer/AnimSprite.h"
#include "../engine/renderer/ShaderRender.h"
#include "../engine/renderer/TextureRender.h"

#include "../engine/managers/PhysicsManager.h"
#include "../engine/managers/GameManager.h"

#include "../engine/physics/Collider.h"

#include "../engine/controllers/PlayerController.h"

#include "../main.h"

#include <iostream>

namespace Game
{
	MainCharacter::MainCharacter(std::shared_ptr<Renderer::Texture2D> texture, std::shared_ptr<Renderer::ShaderProgram> shader,
		const std::string& initSubtextureName, const glm::vec2& startPosition, const glm::vec2& startSize, const float startRotation, const float startMoveSpeed)
		:Pawn(texture, shader, initSubtextureName, startPosition, startSize, startRotation)
	{
		_collider = std::make_shared<Physics::Collider>(EObjectTypes::EOT_Character, this, startPosition, startSize);

		_collider->SetCollisionResponse(EObjectTypes::EOT_Enemy, EResponseType::ERT_Overlap);
		_collider->SetCollisionResponse(EObjectTypes::EOT_Character, EResponseType::ERT_Ignore);
		_collider->SetCollisionResponse(EObjectTypes::EOT_Projectile, EResponseType::ERT_Ignore);
		_collider->SetCollisionResponse(EObjectTypes::EOT_InteractiveObject, EResponseType::ERT_Overlap);

		//_collider->Overlap.Connect(this, &MainCharacter::Overlap);
		_collider->AddOverlapDelegate(this, &MainCharacter::Overlap);
		_collider->Attach(this);

		_health_component = std::make_shared<HealthComponent>(this, 10);

		_weapon_component = std::make_shared<WeaponComponent>(std::move(texture), std::move(shader), "pistol", this, startPosition + (startSize / 2.f), startSize / 4.f, startRotation);

		_controller = new PlayerController(this, 100.f);
	}

	MainCharacter::~MainCharacter()
	{
		if (_controller)
		{
			delete _controller;
			_controller = nullptr;
		}
	}


	void MainCharacter::BeginPlay()
	{
		
	}

	void MainCharacter::Update(float deltaTime)
	{
		_controller->Move(deltaTime);
		Actor::Update(deltaTime);

		if (_health_component->GetInviolabilityTime() > 0.f)
		{
			_health_component->UpdateInviolability(deltaTime);
		}
		_health_component->RenderHealth();

		_weapon_component->Update(deltaTime);
	}

	void MainCharacter::Overlap(Actor* overlappingActor)
	{
		Enemy* enemy = dynamic_cast<Enemy*>(overlappingActor);
		HealActor* heal = dynamic_cast<HealActor*>(overlappingActor);
		if (_health_component->GetInviolabilityTime() <= 0.f)
		{
			if (enemy)
			{
				_health_component->Hurt(enemy->GetOverlapDamage());
				return;
			}
			else
			{
				//std::shared_ptr<Enemy> bullet = std::dynamic_pointer_cast<Enemy>(overlappingActor);
				//here add a damage of bullet and make cast to a bullet class
			}
		}
		else
		{

		}

		if (heal)
		{
			_health_component->Heal(heal->GetHealValue());
			heal->DestroyActor();
		}

	}
}