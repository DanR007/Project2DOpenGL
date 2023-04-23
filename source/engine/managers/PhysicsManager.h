#pragma once

#include <memory>
#include <vector>

#include <glm/vec2.hpp>

#include "../physics/EPhysicsTypes.h"
#include "../physics/RaycastResult.h"

class Actor;

class GameManager;
class PhysicsTests;

class Unit;

namespace Physics 
{
	class Collider;

	class PhysicsManager
	{
	public:
		PhysicsManager(GameManager* world) : _world(world) {}

		bool CanMove(Actor* checkActor, const glm::vec2& delta);
		void CheckOverlapping(std::shared_ptr<Physics::Collider> first_collider);

		void Update();

		bool Raycast(RaycastResult& result, const glm::vec2& start, const glm::vec2& end, const ERaycastTypes& raycast_type,
			Actor* self = nullptr, bool ignore_self = true);

		Unit* GetUnitUnderCursor(const glm::vec2& cursor_pos);
	private:
		bool IsIntersection(const glm::vec2& pos_first_collider, const glm::vec2& size_first_collider, const glm::vec2& pos_second_collider, const glm::vec2& size_second_collider);

		bool IsOverlap(std::shared_ptr<Physics::Collider> first_collider,
			std::shared_ptr<Physics::Collider> second_collider);
		bool IsBlocking(const glm::vec2& delta_pos,
			std::shared_ptr<Physics::Collider> first_collider,
			std::shared_ptr<Physics::Collider> second_collider);

		GameManager* _world;

		friend class PhysicsTests;
	};
}