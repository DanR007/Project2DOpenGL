#include "Controller.h"

#include "../default_classes/Pawn.h"

#include "../managers/PhysicsManager.h"

#include "../../main.h"

Controller::Controller(Game::Pawn* controlledPawn, const float moveSpeed)
{
	_controlled_pawn = controlledPawn;
	_move_speed = moveSpeed;
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
	if (_move_vector != glm::vec2(0.f, 0.f)/* &&
		PhysicsManager::CanMove(_controlled_pawn, _controlled_pawn->GetPosition() + _move_vector * deltaTime * _move_speed)*/)
		_controlled_pawn->SetPosition(_controlled_pawn->GetPosition() + _move_vector * deltaTime * _move_speed);
}

void Controller::SetIgnoreMoveInput(bool isIgnore)
{
	is_ignore_move_input = isIgnore;
}

void Controller::ChangeMoveVector(glm::vec2 inputVector)
{
	_move_vector += inputVector;
}



