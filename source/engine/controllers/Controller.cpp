#include "Controller.h"

#include "../default_classes/Pawn.h"

#include "../managers/GameManager.h"

#include "../AI/AStarRTS.h"

#include "../../main.h"

Controller::Controller(Game::Pawn* controlledPawn, const float moveSpeed)
{
	_controlled_pawn = controlledPawn;
	_move_speed = moveSpeed;

	_a_star = new AStarRTS();
}

Controller::Controller(const float moveSpeed)
{
	_controlled_pawn = nullptr;
	_move_speed = moveSpeed;
}

Controller::Controller()
{
	_controlled_pawn = nullptr;
	_move_speed = 0.f;
}

void Controller::Move(float deltaTime)
{
	if (_move_vector != glm::vec2(0.f, 0.f))
		_controlled_pawn->SetPosition(_controlled_pawn->GetPosition() + _move_vector * deltaTime * _move_speed);
}

void Controller::ChangeMoveVector(glm::vec2 inputVector)
{
	_move_vector += inputVector;
}

void Controller::MakePathForGoal(const Cell& goal, const glm::ivec2& move_from)
{
	_a_star->DevelopPath(move_from, goal);
}