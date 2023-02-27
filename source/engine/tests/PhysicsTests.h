#pragma once

#include "../managers/PhysicsManager.h"
#include "../managers/ResourcesManager.h"

#include "../physics/Collider.h"

#include "../default_classes/Actor.h"

#include "../../game/gameobjects/WallActor.h"
#include "../../game/gameobjects/HealActor.h"

#include "../managers/GameManager.h"

#include <cmath>

class PhysicsTests
{
public:
	PhysicsTests() { manager = new Physics::PhysicsManager(nullptr); }
	~PhysicsTests() { delete manager; }

	bool CheckBlockPhysicsBetweenTwoObjectsMustBeFalse()
	{
		std::shared_ptr<Game::Actor> actor = std::make_shared<Game::Actor>(ResourcesManager::GetTexture("textureAtlas"), ResourcesManager::GetShaderProgram("spriteShader"), "mush1", glm::vec2(0.f),
			glm::vec2(100.f, 100.f), 0.f);
		actor->SetCollider(std::make_shared<Physics::Collider>(EObjectTypes::EOT_Character, actor.get(), glm::vec2(0.f)));
		actor->GetCollider()->SetCollisionResponse(EObjectTypes::EOT_Character, EResponseType::ERT_Ignore);
		actor->GetCollider()->SetCollisionResponse(EObjectTypes::EOT_StaticObject, EResponseType::ERT_Block);


		std::shared_ptr<Game::Objects::Wall> wallActor = std::make_shared<Game::Objects::Wall>(ResourcesManager::GetTexture("textureAtlas"), ResourcesManager::GetShaderProgram("spriteShader"), "wall", glm::vec2(0.f, 101.f),
			glm::vec2(100.f, 100.f), 0.f);

		return manager->IsBlocking(glm::vec2(0.f), actor->GetCollider(), wallActor->GetCollider());
	}
	bool CheckBlockPhysicsBetweenTwoObjectsMustBeTrue()
	{
		std::shared_ptr<Game::Actor> actor = std::make_shared<Game::Actor>(ResourcesManager::GetTexture("textureAtlas"), ResourcesManager::GetShaderProgram("spriteShader"), "mush1", glm::vec2(0.f),
			glm::vec2(100.f, 100.f), 0.f);
		actor->SetCollider(std::make_shared<Physics::Collider>(EObjectTypes::EOT_Character, actor.get(), glm::vec2(0.f)));
		actor->GetCollider()->SetCollisionResponse(EObjectTypes::EOT_Character, EResponseType::ERT_Ignore);
		actor->GetCollider()->SetCollisionResponse(EObjectTypes::EOT_StaticObject, EResponseType::ERT_Block);


		std::shared_ptr<Game::Objects::Wall> wallActor = std::make_shared<Game::Objects::Wall>(ResourcesManager::GetTexture("textureAtlas"), ResourcesManager::GetShaderProgram("spriteShader"), "wall", glm::vec2(0.f, 101.f),
			glm::vec2(100.f, 100.f), 0.f);

		return manager->IsBlocking(glm::vec2(2.f), actor->GetCollider(), wallActor->GetCollider());
	}
	bool CheckOverlappingBetweenTwoObjectsMustBeFalse()
	{
		std::shared_ptr<Game::Actor> actor = std::make_shared<Game::Actor>(ResourcesManager::GetTexture("textureAtlas"), ResourcesManager::GetShaderProgram("spriteShader"), "mush1", glm::vec2(0.f),
			glm::vec2(100.f, 100.f), 0.f);
		actor->SetCollider(std::make_shared<Physics::Collider>(EObjectTypes::EOT_Character, actor.get(), glm::vec2(0.f)));
		actor->GetCollider()->SetCollisionResponse(EObjectTypes::EOT_InteractiveObject, EResponseType::ERT_Overlap);
		std::shared_ptr<Game::HealActor> healActor = std::make_shared<Game::HealActor>(ResourcesManager::GetTexture("textureAtlas"), ResourcesManager::GetShaderProgram("spriteShader"), "wall", glm::vec2(0.f, 101.f),
			glm::vec2(100.f, 100.f), 0.f);
		return manager->IsOverlap(actor->GetCollider(), healActor->GetCollider());
	}
	bool CheckOverlappingBetweenTwoObjectsMustBeTrue()
	{
		std::shared_ptr<Game::Actor> actor = std::make_shared<Game::Actor>(ResourcesManager::GetTexture("textureAtlas"), ResourcesManager::GetShaderProgram("spriteShader"), "mush1", glm::vec2(0.f),
			glm::vec2(100.f, 100.f), 0.f);
		actor->SetCollider(std::make_shared<Physics::Collider>(EObjectTypes::EOT_Character, actor.get(), glm::vec2(0.f)));
		actor->GetCollider()->SetCollisionResponse(EObjectTypes::EOT_InteractiveObject, EResponseType::ERT_Overlap);
		std::shared_ptr<Game::HealActor> healActor = std::make_shared<Game::HealActor>(ResourcesManager::GetTexture("textureAtlas"), ResourcesManager::GetShaderProgram("spriteShader"), "wall", glm::vec2(10.f, 10.f),
			glm::vec2(50.f, 50.f), 0.f);
		return manager->IsOverlap(actor->GetCollider(), healActor->GetCollider());
	}

	bool CheckRaycastMustBeTrueAndPosZero()
	{
		RaycastResult result;
		GetWorld()->SpawnActor<Game::Objects::Wall>("wall", glm::vec2(50), glm::vec2(100.f));
		GetWorld()->GetPhysicsManager()->Raycast(result, glm::vec2(-10), glm::vec2(10), ERaycastTypes::ERT_Visible);
		GetWorld()->Clear();
		return result._is_hit && result._hit_position == glm::vec2(0);
	}
	bool CheckRaycastMustBeFalseBecauseDirectionAwayFromBox()
	{
		RaycastResult result;
		GetWorld()->SpawnActor<Game::Objects::Wall>("wall", glm::vec2(50), glm::vec2(100.f));
		GetWorld()->GetPhysicsManager()->Raycast(result, glm::vec2(-10), glm::vec2(-100), ERaycastTypes::ERT_Visible);
		GetWorld()->Clear();
		return result._is_hit;
	}
	bool CheckRaycastMustBeFalseBecauseRaySmallerThenDistanceToBox()
	{
		RaycastResult result;
		GetWorld()->SpawnActor<Game::Objects::Wall>("wall", glm::vec2(50), glm::vec2(100.f), 45.f);
		GetWorld()->GetPhysicsManager()->Raycast(result, glm::vec2(-10), glm::vec2(0), ERaycastTypes::ERT_Visible);
		GetWorld()->Clear();
		return result._is_hit;
	}
	bool CheckRaycastMustBeTrueAndDistanceEqualDirectionMinusHalfSizeByX()
	{
		RaycastResult result;
		glm::vec2 size = glm::vec2(100.f);
		GetWorld()->SpawnActor<Game::Objects::Wall>("wall", glm::vec2(50), size, 45.f);
		glm::vec2 start = glm::vec2(0.f), end = glm::vec2(50.f);
		glm::vec2 direction = end - start;
		GetWorld()->GetPhysicsManager()->Raycast(result, start, end, ERaycastTypes::ERT_Visible);
		GetWorld()->Clear();
		float distance = (float)std::sqrt(std::pow(direction.x, 2) + std::pow(direction.y, 2)) - size.x / 2;
		return result._is_hit && std::abs(result._distance - distance) < 0.0001;
	}
private:
	Physics::PhysicsManager* manager;
};