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

	static void IsOverlap(std::shared_ptr<Physics::Collider> checkCollider);
};