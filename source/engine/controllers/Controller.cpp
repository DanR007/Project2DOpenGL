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
	if(!_controlled_pawn)
	{
#ifdef DEBUG_MOVEMENT
	std::cout << "_controlled_pawn is nullptr" << std::endl;
#endif //DEBUG_MOVEMENT
	return;
	}

	if (!_complete_path)
	{
#ifdef DEBUG_MOVEMENT
	std::cout << "path is not complete" << std::endl;
#endif //DEBUG_MOVEMENT
		float distance = std::sqrt(std::pow(_node_coord.x - _controlled_pawn->GetPosition().x, 2) + std::pow(_node_coord.y - _controlled_pawn->GetPosition().y, 2));
		_move_vector = (_node_coord - _controlled_pawn->GetPosition()) / distance;
		
		//если двигаться некуда, то говорим что путь закончен
		if (_move_vector != glm::vec2(0.f, 0.f))
		{
#ifdef DEBUG_MOVEMENT
	std::cout << "_move_vector is not zero vector" << std::endl;
#endif //DEBUG_MOVEMENT
			if(GetEngine()->GetWorld()->GetNavMesh()->InMap(_node_in_map_coord))
			{
				float cost = GetWorld()->GetNavMesh()->GetMap()[_node_in_map_coord.y][_node_in_map_coord.x]->_cost;
				glm::vec2 movement = _move_vector * deltaTime * _move_speed / cost;
				//if distance less than our length of movement then choice new small goal
				//else move to movement + position
				if (deltaTime * _move_speed / cost > distance)
				{
	#ifdef DEBUG_MOVEMENT
		std::cout << "movement is greater than distance" << std::endl;
	#endif //DEBUG_MOVEMENT
					_controlled_pawn->Move(_node_coord);

					SetNewNode(_a_star->GetNextNode());
				}
				else
				{
	#ifdef DEBUG_MOVEMENT
		std::cout << "movement is less than distance" << std::endl;
	#endif //DEBUG_MOVEMENT
					_controlled_pawn->Move(_controlled_pawn->GetPosition() + movement);
				}
			}
			else
			{
#ifdef DEBUG_MOVEMENT
		std::cout << "Node does not contain in map" << std::endl;
#endif //DEBUG_MOVEMENT				
			}
		}
		else
		{
#ifdef DEBUG_MOVEMENT
	std::cout << "_move_vector is zero vector" << std::endl;
#endif //DEBUG_MOVEMENT
			//если двигаться некуда, то говорим что путь закончен
			_complete_path = true;
			if (_controlled_pawn)
			{
				_controlled_pawn->MakePathComplete();
			}
		}
	}
		
}

void Controller::ChangeMoveVector(glm::vec2 inputVector)
{
	_move_vector += inputVector;
}

void Controller::MakePathForGoal(Cell* goal, const glm::ivec2& move_from)
{
	if(_a_star)
	{
		_node_in_map_coord = _controlled_pawn->GetMapPosition();

		//if path doesn't complete then 
		//pawn continue move to current target but path creating from
		//current target to new target
		if (!_complete_path)
		{
			_controlled_pawn->MakePathComplete();
			_a_star->Clear();
		}

		_complete_path = false;
		//запоминаем в юните текущую цель нашего пути
		if (_controlled_pawn)
		{
			_controlled_pawn->SetGoal(_a_star->DevelopPath(move_from, goal));
		}
#ifdef DEBUG_MOVEMENT
	std::cout << "path is ok" << std::endl;
#endif //DEBUG_MOVEMENT
		//привязываем отображение нашего пути к текущему юниту
		if(_controlled_pawn->GetGoal())
		{
			_controlled_pawn->GetGoal()->SetUnit(_controlled_pawn);
		}
		else
		{
#ifdef DEBUG_MOVEMENT
	std::cout << "goal is nullptr" << std::endl;
#endif //DEBUG_MOVEMENT
		}
		SetNewNode(_node_in_map_coord);

	}
	else
	{
#ifdef DEBUG_MOVEMENT
	std::cout << "AStar in controller is empty" << std::endl;
#endif //DEBUG_MOVEMENT
	}
}


//set map position to unit and choice new map position
//if path doesn't empty
void Controller::SetNewNode(const glm::ivec2& map_coord)
{
	_controlled_pawn->SetMapPosition(_node_in_map_coord);

	//отрицательная позиция показывает что больше в _a_star не хранится узлов для перемещения
	if (map_coord == glm::ivec2(-1, -1))
	{
		if (_controlled_pawn)
		{
			_controlled_pawn->MakePathComplete();
		}
		_complete_path = true;
		return;
	}

	_node_in_map_coord = map_coord;
	_node_coord = GetWorld()->ConvertToWindowSpace(map_coord);
}
