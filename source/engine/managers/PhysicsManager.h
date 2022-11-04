#pragma once

#include <memory>
#include <vector>

#include <glm/vec2.hpp>

namespace Game { class Actor; }

namespace Physics { class Collider; }

class GameManager;

class PhysicsManager
{
public:
	PhysicsManager(GameManager* world) : _world(world) {}

	bool CanMove(Game::Actor* checkActor, const glm::vec2& nextPosition);
	void CheckOverlapping(std::shared_ptr<Physics::Collider> checkCollider);

private:
	bool IsOverlap(const glm::vec2& posCurrentCollider, const glm::vec2& checkPosition, 
		const glm::vec2& sizeActor, const glm::vec2& sizeCurrentCollider,
		std::shared_ptr<Physics::Collider> checkCollider,
		std::shared_ptr<Physics::Collider> currentActorCollider);
	bool IsBlocking(const glm::vec2& posCurrentCollider, const glm::vec2& checkPosition, 
		const glm::vec2& sizeActor, const glm::vec2& sizeCurrentCollider,
		std::shared_ptr<Physics::Collider> checkCollider,
		std::shared_ptr<Physics::Collider> currentActorCollider);

	GameManager* _world;

	friend class PhysicsTests;
};