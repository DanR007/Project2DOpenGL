#pragma once

#include "../managers/PhysicsManager.h"
#include "../managers/ResourcesManager.h"

#include "../physics/Collider.h"

#include "../default_classes/Actor.h"

#include "../../game/gameobjects/WallActor.h"
#include "../../game/gameobjects/HealActor.h"

class PhysicsTests
{
public:
	PhysicsTests() { manager = new PhysicsManager(nullptr); }
	~PhysicsTests() { delete manager; }

	bool CheckBlockPhysicsBetweenTwoObjects()
	{
		std::shared_ptr<Game::Actor> actor = std::make_shared<Game::Actor>(ResourcesManager::GetTexture("textureAtlas"), ResourcesManager::GetShaderProgram("spriteShader"), "mush1", glm::vec2(0.f),
			glm::vec2(100.f, 100.f), 0.f);
		actor->SetCollider(std::make_shared<Physics::Collider>(EObjectTypes::EOT_Character, glm::vec2(0.f)));
		actor->GetCollider()->SetCollisionResponse(EObjectTypes::EOT_Character, EResponseType::ERT_Ignore);
		actor->GetCollider()->SetCollisionResponse(EObjectTypes::EOT_StaticObject, EResponseType::ERT_Block);
		std::shared_ptr<Game::Objects::Wall> wallActor = std::make_shared<Game::Objects::Wall>(ResourcesManager::GetTexture("textureAtlas"), ResourcesManager::GetShaderProgram("spriteShader"), "wall", glm::vec2(0.f, 101.f),
			glm::vec2(100.f, 100.f), 0.f);
		return manager->IsBlocking(wallActor->GetCollider()->GetPosition(), actor->GetCollider()->GetPosition() + glm::vec2(0.f, 20.f),
			actor->GetCollider()->GetSize(), wallActor->GetCollider()->GetSize(), actor->GetCollider(), wallActor->GetCollider());
	}

	bool CheckOverlappingBetweenTwoObjects()
	{
		std::shared_ptr<Game::Actor> actor = std::make_shared<Game::Actor>(ResourcesManager::GetTexture("textureAtlas"), ResourcesManager::GetShaderProgram("spriteShader"), "mush1", glm::vec2(0.f),
			glm::vec2(100.f, 100.f), 0.f);
		actor->SetCollider(std::make_shared<Physics::Collider>(EObjectTypes::EOT_Character, glm::vec2(0.f)));
		actor->GetCollider()->SetCollisionResponse(EObjectTypes::EOT_InteractiveObject, EResponseType::ERT_Overlap);
		std::shared_ptr<Game::HealActor> healActor = std::make_shared<Game::HealActor>(ResourcesManager::GetTexture("textureAtlas"), ResourcesManager::GetShaderProgram("spriteShader"), "wall", glm::vec2(0.f, 101.f),
			glm::vec2(100.f, 100.f), 0.f);
		return manager->IsOverlap(healActor->GetCollider()->GetPosition(), actor->GetCollider()->GetPosition() + glm::vec2(0.f, 20.f),
			actor->GetCollider()->GetSize(), healActor->GetCollider()->GetSize(), actor->GetCollider(), healActor->GetCollider());
	}

private:
	PhysicsManager* manager;
};