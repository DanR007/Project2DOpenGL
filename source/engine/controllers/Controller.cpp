#include "Controller.h"

#include "../../game/Pawn.h"

#include "../managers/PhysicsManager.h"

#include "../../main.h"

/*Controller::Controller(std::shared_ptr<Game::Pawn> controlledPawn, const float moveSpeed)
{
	controlled_pawn = controlledPawn;
	move_speed = moveSpeed;
}*/

Controller::Controller(const float moveSpeed)
{
	move_speed = moveSpeed;
}

Controller::Controller()
{
	move_speed = 0.f;
}

void Controller::Move(float deltaTime)
{
	//if (move_vector != glm::vec2(0.f, 0.f) && 
		//PhysicsManager::CanMove(all_actors, controlled_pawn->position + move_vector * deltaTime * move_speed, controlled_pawn->size))
		//controlled_pawn->SetPosition(controlled_pawn->position + move_vector * deltaTime * move_speed);
}

void Controller::SetIgnoreMoveInput(bool isIgnore)
{
	is_ignore_move_input = isIgnore;
}

void Controller::ChangeMoveVector(glm::vec2 inputVector)
{
	move_vector += inputVector;
}



