#include "EnemyController.h"

#include "../AI/AStar.h"

#include "../default_classes/Pawn.h"

#include "../../engine/managers/PhysicsManager.h"

EnemyController::EnemyController(Game::Pawn* controlled_pawn, const float move_speed)
	: Controller(controlled_pawn, move_speed)
{
	_a_star = new AStar();

	current_patrol_point = _controlled_pawn->GetPosition();
}

void EnemyController::Move(float deltaTime)
{
	double length = std::sqrt(std::pow((current_patrol_point - _controlled_pawn->GetPosition()).x, 2) + std::pow((current_patrol_point - _controlled_pawn->GetPosition()).y, 2));
	//std::cout << (current_patrol_point - position).length() << std::endl;

	if (length < 0.2f)
	{
		PointReached();
		current_patrol_point = patrol_points[index];
	}
	else
	{
		//move_vector = _a_star->DevelopPath(_position, current_patrol_point, this);
		_move_vector = glm::vec2(glm::vec2(current_patrol_point - _controlled_pawn->GetPosition()).x / length,
			glm::vec2(current_patrol_point - _controlled_pawn->GetPosition()).y / length);

		if (_move_vector != glm::vec2(0.f, 0.f) /*&&
			PhysicsManager::CanMove(_controlled_pawn, _controlled_pawn->GetPosition() + _move_vector * deltaTime * _move_speed)*/)
			_controlled_pawn->SetPosition(_controlled_pawn->GetPosition() + _move_vector * deltaTime * _move_speed);
	}
}

void EnemyController::ChangeMoveVector(glm::vec2 inputVector)
{

}
void EnemyController::PointReached()
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

void EnemyController::ChangePatrolPointsCoordinate(const glm::vec2& value)
{
	for (glm::vec2& point : patrol_points)
	{
		point += value;
	}

	current_patrol_point += value;
}

void EnemyController::SetPatrolPoints(const std::vector<glm::vec2>& patrolPoints)
{
	patrol_points = patrolPoints;
	if (!patrolPoints.empty())
		current_patrol_point = patrolPoints[index];
}