#include "PlayerController.h"

#include "../../game/MainCharacter.h"

#include "../managers/PhysicsManager.h"


void PlayerController::Move(float deltaTime)
{
	//if (!is_ignore_move_input && move_vector != glm::vec2(0.f, 0.f) &&
		//PhysicsManager::CanMove(std::move(all_actors), controlled_character->position + move_vector * deltaTime * move_speed, controlled_character->size))
	/*{
		for (std::shared_ptr<Game::Actor> actor : all_actors)
		{
			actor->SetPosition(actor->GetPosition() - move_vector * deltaTime * move_speed);
		}
	}*/
}

void PlayerController::ChangeMoveVector(glm::vec2 inputVector)
{
	move_vector += inputVector;
}

void PlayerController::Input(GLFWwindow* currentWindow, int key, int scancode, int action, int mode)
{
	switch (action)
	{
	case GLFW_PRESS:
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(currentWindow, GLFW_TRUE);
			break;
		case GLFW_KEY_W:
			if (!is_ignore_move_input)
				ChangeMoveVector(up_vector);
			break;
		case GLFW_KEY_S:
			if (!is_ignore_move_input)
				ChangeMoveVector(up_vector * -1.f);
			break;
		case GLFW_KEY_D:
			if (!is_ignore_move_input)
				ChangeMoveVector(right_vector);
			break;
		case GLFW_KEY_A:
			if (!is_ignore_move_input)
				ChangeMoveVector(right_vector * -1.f);
			break;
		}
		break;
	case GLFW_RELEASE:
		switch (key)
		{
		case GLFW_KEY_W:
			ChangeMoveVector(up_vector * -1.f);
			break;
		case GLFW_KEY_S:
			ChangeMoveVector(up_vector);
			break;
		case GLFW_KEY_D:
			ChangeMoveVector(right_vector * -1.f);
			break;
		case GLFW_KEY_A:
			ChangeMoveVector(right_vector);
			break;
		}
		break;
	case GLFW_REPEAT:

		break;
	}
}

void PlayerController::SetCharacter(Game::MainCharacter* controlledCharacter)
{
	controlled_character.reset(controlledCharacter);
}

