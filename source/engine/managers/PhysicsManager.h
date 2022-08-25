#pragma once

#include <memory>
#include <vector>

#include <glm/vec2.hpp>

namespace Game
{ 
	class Actor;
}

namespace Physics
{ 
	class Collider;
}

class PhysicsManager
{
public:
	static bool CanMove(Game::Actor* checkActor, const glm::vec2& nextPosition);

	static void CheckOverlapping(std::shared_ptr<Physics::Collider> checkCollider);
	static bool IsOverlap(const glm::vec2& posCurrentCollider, const glm::vec2& checkPosition, const glm::vec2& sizeActor, const glm::vec2& sizeCurrentCollider,
		std::shared_ptr<Physics::Collider> checkCollider,
		std::shared_ptr<Physics::Collider> currentActorCollider);
	static bool IsBlocking(const glm::vec2& posCurrentCollider, const glm::vec2& checkPosition, const glm::vec2& sizeActor, const glm::vec2& sizeCurrentCollider,
		std::shared_ptr<Physics::Collider> checkCollider,
		std::shared_ptr<Physics::Collider> currentActorCollider);
};