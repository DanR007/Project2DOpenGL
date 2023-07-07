#include "Controller.h"

#include "../managers/GameManager.h"

#include "../AI/AStarRTS.h"
#include "../AI/NavMesh.h"

#include "../../main.h"

#include "../../game/gameobjects/Unit.h"
#include "../../game/gameobjects/Goal.h"

Controller::Controller(Unit* controlledPawn, const float moveSpeed)
{
	_controlled_pawn = controlledPawn;
	_move_speed = moveSpeed;

	_a_star = new AStarRTS();
}

Controller::Controller(const float moveSpeed)
{
	_controlled_pawn = nullptr;
	_move_speed = moveSpeed;

	_a_star = new AStarRTS();
}

Controller::Controller()
{
	_controlled_pawn = nullptr;
	_move_speed = 0.f;

	_a_star = new AStarRTS();
}

Controller::~Controller()
{
	if (_a_star)
	{
		delete _a_star;
		_a_star = nullptr;
	}
#ifdef DEBUG
	std::cout << "Destroy Controller" << std::endl;
#endif
}

//move while path doesn't complete 
void Controller::Move(float deltaTime)
{
	if (!_complete_path)
	{
		float distance = std::sqrt(std::pow(_goal.x - _controlled_pawn->GetPosition().x, 2) + std::pow(_goal.y - _controlled_pawn->GetPosition().y, 2));
		_move_vector = (_goal - _controlled_pawn->GetPosition()) / distance;
		if (_move_vector != glm::vec2(0.f, 0.f))
		{
			float cost = GetWorld()->GetNavMesh()->GetMap()[_goal_int.y][_goal_int.x]._cost;
			
			if (deltaTime * _move_speed / cost > distance)
			{
				_controlled_pawn->Move(_goal);

				SetNewGoal(_a_star->GetNextMapGoal());
			}
			else
			{
				_controlled_pawn->Move(_controlled_pawn->GetPosition() + _move_vector * deltaTime * _move_speed / cost);
			}
		}
		else
		{
			_complete_path = true;
			if (_controlled_pawn)
				_controlled_pawn->PathComplete();
		}
	}
		
}

void Controller::ChangeMoveVector(glm::vec2 inputVector)
{
	_move_vector += inputVector;
}

void Controller::MakePathForGoal(const Cell& goal, const glm::ivec2& move_from)
{
	_goal_int = _controlled_pawn->GetMapPosition();

	//if path doesn't complete then 
	//pawn continue move to current target but path creating from
	//current target to new target
	if (!_complete_path)
	{
		_controlled_pawn->PathComplete();
		_a_star->Clear();
	}

	_complete_path = false;
	if (_controlled_pawn)
		_controlled_pawn->SetGoal(_a_star->DevelopPath(move_from, goal));

	std::cout << "path is ok" << std::endl;

	_controlled_pawn->GetGoal()->SetUnit(_controlled_pawn);

	SetNewGoal(_a_star->GetNextMapGoal());
}


//set map position to unit and choice new map position
//if path doesn't empty
void Controller::SetNewGoal(const glm::ivec2& map_coord)
{
	_controlled_pawn->SetMapPosition(_goal_int);
	if (map_coord == glm::ivec2(-1, -1))
	{
		if (_controlled_pawn)
		{
			_controlled_pawn->PathComplete();
		}
		_complete_path = true;
		return;
	}

	_goal_int = map_coord;
	_goal = GetWorld()->ConvertToWindowSpace(map_coord);
}
