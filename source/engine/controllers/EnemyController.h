#pragma once

#include "Controller.h"

#include <vector>
#include <glm/vec2.hpp>

class AStar;

class EnemyController : public Controller
{
public:
	EnemyController(Game::Pawn* controlled_pawn, const float move_speed);

	~EnemyController();

	void Move(float deltaTime) override;
	void ChangeMoveVector(glm::vec2 inputVector) override;

	virtual void PointReached();

	virtual void ChangePatrolPointsCoordinate(const glm::vec2& value);

	virtual void SetPatrolPoints(const std::vector<glm::vec2>& patrolPoints);
private:
	std::vector<glm::vec2> patrol_points;

	glm::vec2 current_patrol_point;

	int patrol_direction = 1;
	size_t index = 0;
};