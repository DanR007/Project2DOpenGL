#include "MeleeEnemy.h"

#include "../../engine/managers/PhysicsManager.h"
#include "../../engine/managers/GameManager.h"

#include "../../main.h"

#include <cmath>
#include <iostream>
namespace Game
{
	MeleeEnemy::MeleeEnemy(std::shared_ptr<Renderer::Texture2D> texture, std::shared_ptr<Renderer::ShaderProgram> shader, 
		const std::string& initSubtextureName, const std::vector<glm::vec2>& patrolPoints,
		const glm::vec2& startPosition, const glm::vec2& startSize, const float startRotation, const float moveSpeed)
		: Pawn(std::move(texture), std::move(shader), initSubtextureName, startPosition, startSize, startRotation, moveSpeed)
	{
		patrol_points = patrolPoints;
		if(!patrolPoints.empty())
			current_patrol_point = patrolPoints[index];
	}

	void MeleeEnemy::Move(const float deltaTime)
	{
		double length = std::sqrt(std::pow((current_patrol_point - position).x, 2) + std::pow((current_patrol_point - position).y, 2));
		//std::cout << (current_patrol_point - position).length() << std::endl;
		if (length < 0.2f)
		{
			PointReached();
			current_patrol_point = patrol_points[index];
		}
		else
		{
			move_vector = glm::vec2(glm::vec2(current_patrol_point - position).x / length,
				glm::vec2(current_patrol_point - position).y / length);

			if (move_vector != glm::vec2(0.f, 0.f) &&
				PhysicsManager::CanMove(this, position + move_vector * deltaTime * move_speed, size))
				SetPosition(position + move_vector * deltaTime * move_speed);
		}
	}

	void MeleeEnemy::PointReached()
	{
		if (index + patrol_direction >= patrol_points.size())
		{
			patrol_direction *= -1;
		}
		else
		{
			if (index + patrol_direction < 0)
			{
				patrol_direction *= -1;
			}
		}
		index += patrol_direction;
	}

	void MeleeEnemy::ChangePatrolPointsCoordinate(const glm::vec2& value)
	{
		for (glm::vec2& point : patrol_points)
		{
			point += value;
		}

		current_patrol_point += value;
	}
	
}