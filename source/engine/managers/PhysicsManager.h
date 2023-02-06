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

	bool CanMove(Game::Actor* checkActor, const glm::vec2& delta);
	void CheckOverlapping(std::shared_ptr<Physics::Collider> first_collider);

	void Update();
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